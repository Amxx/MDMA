#include "zone.h"

Zone::Zone()
{
	for(int i = 0; i < 9; ++i)
		signal[i] = new unsigned char[3];
}

Zone::Zone(QPoint _p1, QPoint _p2, int _t)
{
	name = "New Zone";
	pos[0] = _p1;
	pos[1] = _p2;
	tab = _t;
	type = MDMA::FADER;
	for(int i = 0; i < 9; ++i)
	{
		active[i] = MDMA::NOTHING;
		signal[i] = new unsigned char[3];
		signal[i][0] = 0;
		signal[i][1] = 0;
		signal[i][2] = 0;
	}
	variable[0] = false;
	variable[1] = false;
}

Zone::Zone(const Zone& cpy)
{
	name = cpy.name;
	pos[0] = cpy.pos[0];
	pos[1] = cpy.pos[1];
	tab = cpy.tab;
	type = cpy.type;
	for(int i = 0; i < 9; ++i)
	{
		active[i] = cpy.active[i];
		signal[i] = new unsigned char[3];
		signal[i][0] = cpy.signal[i][0];
		signal[i][1] = cpy.signal[i][1];
		signal[i][2] = cpy.signal[i][2];
	}
}


Zone::~Zone()
{
	for(int i = 0; i < 9; ++i)
		delete[] signal[i];
}

void Zone::display(QPainter& painter)
{
	QFont font;
	font.setPointSize(8);
	painter.setFont(font);

	switch(type)
	{
		case MDMA::FADER :
		{
			painter.fillRect(QRect(pos[0], pos[1]), MDMA::typeToFillColor(type, emph_display));
			painter.setPen(QPen(QBrush(MDMA::typeToBorderColor(type, emph_display)), 3, Qt::SolidLine, Qt::SquareCap));
			if(MDMA::isMidi(active[MDMA::EVENT_X]))
			{
				int x_min = std::min(pos[0].x(), pos[1].x());
				int x_max = std::max(pos[0].x(), pos[1].x());
				int x_value = x_min + (x_max - x_min) * signal[MDMA::EVENT_X][variable[0]?1:2]/127;
				painter.drawLine(QPoint(x_value, pos[0].y()), QPoint(x_value, pos[1].y()));
			}
			if(MDMA::isMidi(active[MDMA::EVENT_Y]))
			{
				int y_min = std::min(pos[0].y(), pos[1].y());
				int y_max = std::max(pos[0].y(), pos[1].y());
				int y_value = y_max - (y_max - y_min) * signal[MDMA::EVENT_Y][variable[1]?1:2]/127;
				painter.drawLine(QPoint(pos[0].x(), y_value), QPoint(pos[1].x(), y_value));
			}

			painter.setPen(MDMA::textColor);
			painter.drawText(std::min(pos[0].x(), pos[1].x())+2, std::min(pos[0].y(), pos[1].y())+10, name);
			break;
		}

		case MDMA::PAD :
		{
			painter.fillRect(QRect(pos[0], pos[1]), MDMA::typeToFillColor(type, emph_display));

			painter.setPen(MDMA::textColor);
			painter.drawText(std::min(pos[0].x(), pos[1].x())+2, std::min(pos[0].y(), pos[1].y())+10, name);
			break;
		}

		case MDMA::SEGMENT :
		{
			QPolygon poly;
			QPoint center, director;

			painter.setPen(QPen(QBrush(MDMA::typeToFillColor(type, emph_display)), 3, Qt::SolidLine, Qt::RoundCap));
			painter.drawLine(pos[0], pos[1]);

			painter.setPen(QPen(QBrush(MDMA::typeToFillColor(type, emph_display)), 1, Qt::SolidLine, Qt::RoundCap));
			painter.setBrush(QBrush(MDMA::typeToFillColor(type, emph_display)));
			center = (pos[0]+pos[1])/2;
			director = pos[0]-pos[1];
			director *= 20/sqrt(director.x()*director.x()+director.y()*director.y());
			poly << center + director/2;
			poly << center + sqrt(3)*QPoint(-director.y(), director.x())/2;
			poly << center - director/2;
			painter.drawPolygon(poly);

			painter.setPen(MDMA::textColor);
			painter.drawText(pos[(pos[0].y()<pos[1].y() || pos[0].x()<pos[1].x())?0:1], name);
			break;
		}
	}
}

MDMA::signal Zone::getMidi(MDMA::event ev)
{
	MDMA::signal midi_signal = NULL;
	switch(active[ev])
	{
		case MDMA::NOTE_OFF:
		case MDMA::NOTE_ON:
		case MDMA::POLYFONIC_AFTERTOUCH:
		case MDMA::CONTROL_CHANGE:
		case MDMA::PROGRAM_CHANGE:
		case MDMA::CHANNEL_AFTERTOUCH:
		case MDMA::PITCH_BENDING:
		{
			midi_signal = new unsigned char[3];
			midi_signal[0] = 0x80 | (active[ev] << 4) | signal[ev][0];
			midi_signal[1] = /*0x80 |*/ signal[ev][1];
			midi_signal[2] = /*0x80 |*/ signal[ev][2];
			break;
		}
		case MDMA::GOTO_TAB1:
		case MDMA::GOTO_TAB2:
		case MDMA::GOTO_TAB3:
		case MDMA::NOTHING:
			break;
	}
	return midi_signal;
}

QList<MDMA::event> Zone::update(QMap<int,Pointer>& pts)
{
	QList<MDMA::event> msgs;
	emph_display = false;

	for(Pointer& pt : pts)
	{
		switch(type)
		{
			case MDMA::FADER:
			{
				QRect rect(pos[0], pos[1]);
				rect = rect.normalized();

				if(rect.contains(pt.vects[POS][CURRENT]) && !pt.open[CURRENT])
				{
					emph_display = true;
					if(active[MDMA::EVENT_X] != MDMA::NOTHING)
					{
						int x_value = 0x7F * (pt.vects[POS][CURRENT].x() - rect.x()) / rect.height();
						int var = variable[0]?1:2;
						if(std::abs(signal[MDMA::EVENT_X][var] - x_value) > MDMA::SEUIL)
						{
							signal[MDMA::EVENT_X][var] = x_value;
							msgs << MDMA::EVENT_X;
						}
					}
					if(active[MDMA::EVENT_Y] != MDMA::NOTHING)
					{
						int y_value = 0x7F * (rect.y() + rect.height() - pt.vects[POS][CURRENT].y()) / rect.height();
						int var = variable[0]?1:2;
						if(std::abs(signal[MDMA::EVENT_Y][var] - y_value) > MDMA::SEUIL)
						{
							signal[MDMA::EVENT_Y][var] = y_value;
							msgs << MDMA::EVENT_Y;
						}
					}
				}
				break;
			}

			case MDMA::PAD:
			{
				QRect rect(pos[0], pos[1]);
				if(rect.contains(pt.vects[POS][CURRENT]) && !rect.contains(pt.vects[POS][PREVIOU]) && active[MDMA::ENTER] != MDMA::NOTHING)
				{
					emph_display = true;
					msgs << MDMA::ENTER;
				}
				if(!rect.contains(pt.vects[POS][CURRENT]) && rect.contains(pt.vects[POS][PREVIOU]) && active[MDMA::EXIT] != MDMA::NOTHING)
				{
					emph_display = true;
					msgs << MDMA::EXIT;
				}
				if(rect.contains(pt.vects[POS][CURRENT]) && pt.open[CURRENT] && !pt.open[PREVIOU] && active[MDMA::OPEN] != MDMA::NOTHING)
				{
					emph_display = true;
					msgs << MDMA::OPEN;
				}
				if(rect.contains(pt.vects[POS][CURRENT]) && !pt.open[CURRENT] && pt.open[PREVIOU] && active[MDMA::OPEN] != MDMA::NOTHING)
				{
					emph_display = true;
					msgs << MDMA::CLOSE;
				}

				/*
				 * implementer la frappe !!!!
				 */

				break;
			}

			case MDMA::SEGMENT:
			{
				QLineF vect_hand = QLineF(QPointF(pt.vects[POS][CURRENT]),QPointF(pt.vects[POS][PREVIOU]));
				QLineF vect_segm = QLineF(QPointF(pos[0]), QPointF(pos[1]));
				QPointF intersect_point;
				if(vect_segm.intersect(vect_hand, &intersect_point) == QLineF::BoundedIntersection)
				{
					if(vect_segm.dx() * vect_hand.dy() - vect_segm.dy() * vect_hand.dx() > 0)
					{
						if(active[MDMA::IN] != MDMA::NOTHING)
						{
							emph_display = true;
							msgs << MDMA::IN;
						}
					}
					else
					{
						if(active[MDMA::OUT] != MDMA::NOTHING)
						{
							emph_display = true;
							msgs << MDMA::OUT;
						}
					}
				}
				break;
			}
		}
	}
	return msgs;
}
