#include "eventzone.h"

EventZone::EventZone()
{
	for(int i=0; i<9; i++)
		signal[i] = new unsigned char[3];
}
::
EventZone::EventZone(QPoint _P1, QPoint _P2, int _tab) :
	name("New Zone"),
	P1(_P1),
	P2(_P2),
	tab(_tab),
    type(MDMA::FADER)
{
	emph_display = false;
	for(int i=0; i<3; i++)
	{
		is_active[i] = false;
		hand_in[i] = false;
		hand_open[i] = false;
	}
    for(int i=0; i<9; i++)
	{
		active[i] = MDMA::NOTHING;
		signal[i] = new unsigned char[3];
		signal[i][0] = 0;
		signal[i][1] = 0;
		signal[i][2] = 0;
	}
	for(int i=0; i<2; i++)
			variable[i] = false;

}

EventZone::EventZone(const EventZone &cpy) :
	name(cpy.name),
	P1(cpy.P1),
	P2(cpy.P2),
	tab(cpy.tab),
    type(cpy.type)
{
	emph_display = false;
	for(int i=0; i<3; i++)
	{
		is_active[i] = false;
		hand_in[i] = false;
		hand_open[i] = false;
	}
	for(int i=0; i<9; i++)
	{
		active[i] = cpy.active[i];
		signal[i] = new unsigned char[3];
		signal[i][0] = cpy.signal[i][0];
		signal[i][1] = cpy.signal[i][1];
		signal[i][2] = cpy.signal[i][2];
	}
	for(int i=0; i<2; i++)
			variable[i] = cpy.variable[i];

}

EventZone::~EventZone()
{
	for(int i=0; i<9; i++)
		delete[] signal[i];
}

// ============================================================================================

void EventZone::display(QPainter& painter)
{
	QFont font;
	font.setPointSize(8);
	painter.setFont(font);

	switch(type)
	{
		case MDMA::FADER :
		{
			//painter.setPen(QPen(QBrush(MDMA::type_to_border_color(type, active)), 0, Qt::SolidLine, Qt::SquareCap));
			//painter.drawRect(QRect(P1,P2));

			painter.fillRect(QRect(P1, P2), MDMA::type_to_fill_color(type, emph_display));
			painter.setPen(QPen(QBrush(MDMA::type_to_border_color(type, emph_display)), 3, Qt::SolidLine, Qt::SquareCap));
			if(MDMA::is_midi(active[MDMA::EVENT_X]))
			{
				int x_min = std::min(P1.x(), P2.x());
				int x_max = std::max(P1.x(), P2.x());
				int x_value = x_min + (x_max - x_min) * signal[MDMA::EVENT_X][variable[0]?1:2]/127;
				painter.drawLine(QPoint(x_value, P1.y()), QPoint(x_value, P2.y()));
			}
			if(MDMA::is_midi(active[MDMA::EVENT_Y]))
			{
				int y_min = std::min(P1.y(), P2.y());
				int y_max = std::max(P1.y(), P2.y());
				int y_value = y_max - (y_max - y_min) * signal[MDMA::EVENT_Y][variable[1]?1:2]/127;
				painter.drawLine(QPoint(P1.x(), y_value), QPoint(P2.x(), y_value));
			}

			painter.setPen(MDMA::text_color);
			painter.drawText(std::min(P1.x(), P2.x())+2, std::min(P1.y(), P2.y())+10, name);
			break;
		}

		case MDMA::PAD :
		{
			//painter.setPen(QPen(QBrush(MDMA::type_to_border_color(type, active)), 0, Qt::SolidLine, Qt::SquareCap));
			//painter.drawRect(QRect(P1,P2));
			painter.fillRect(QRect(P1, P2), MDMA::type_to_fill_color(type, emph_display));

			painter.setPen(MDMA::text_color);
			painter.drawText(std::min(P1.x(), P2.x())+2, std::min(P1.y(), P2.y())+10, name);
			break;
		}

		case MDMA::SEGMENT :
		{
			QPolygon poly;
			QPoint center, director;

			painter.setPen(QPen(QBrush(MDMA::type_to_fill_color(type, emph_display)), 3, Qt::SolidLine, Qt::RoundCap));
			painter.drawLine(P1, P2);

			painter.setPen(QPen(QBrush(MDMA::type_to_fill_color(type, emph_display)), 1, Qt::SolidLine, Qt::RoundCap));
			painter.setBrush(QBrush(MDMA::type_to_fill_color(type, emph_display)));
			center = (P1+P2)/2;
			director = P1-P2;
			director *= 20/sqrt(director.x()*director.x()+director.y()*director.y());
			poly << center + director/2;
			poly << center + sqrt(3)*QPoint(-director.y(), director.x())/2;
			poly << center - director/2;
			painter.drawPolygon(poly);

			painter.setPen(MDMA::text_color);
			painter.drawText((P1.y()<P2.y() || P1.x()<P2.x())?P1:P2, name);
			break;
		}
	}
}

MDMA::signal EventZone::getMidi(MDMA::event ev)
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

// ============================================================================================

QList<MDMA::event> EventZone::update(HandDescriptor& main)
{
    QList<MDMA::event> msgs;
	is_active[main.id] = false;
	switch(type)
	{
		case MDMA::FADER:
		{
			QRect rect(P1,P2);
            rect = rect.normalized();

			if(rect.contains(main.curr_pos) && !main.curr_open)
			{
				is_active[main.id] = true;
				if(active[MDMA::EVENT_X] != MDMA::NOTHING)
				{
					int x_value = (main.curr_pos.x() - rect.x())*127/rect.width();
					if(variable[0])
						signal[MDMA::EVENT_X][1] = x_value;
					else
						signal[MDMA::EVENT_X][2] = x_value;
					msgs << MDMA::EVENT_X;
				}
				if(active[MDMA::EVENT_Y] != MDMA::NOTHING)
				{
					int y_value = (rect.y() + rect.height() - main.curr_pos.y())*127/rect.height();
					if(variable[1])
						signal[MDMA::EVENT_Y][1] = y_value;
					else
						signal[MDMA::EVENT_Y][2] = y_value;
					msgs << MDMA::EVENT_Y;
				}
			}
			/*
            if(!rect.contains(main.curr_pos))
            {
				is_active[main.id] = false;
				hand_in[main.id] = false;
				hand_open[main.id] = false;
            }
            else
            {
				if(main.curr_open)
                {
					hand_open[main.id] = true;
					is_active[main.id] = false;
                }
				else if(hand_in[main.id] && hand_open[main.id] && !main.curr_open)
                {
					hand_open[main.id] = false;
					is_active[main.id] = true;
                }
				hand_in[main.id] = true;
            }

			if(!is_active[main.id]) break;

            if(active[MDMA::EVENT_X] != MDMA::NOTHING)
			{
                signal[MDMA::EVENT_X][MDMA::is_midi(active[MDMA::EVENT_X])] = (main.curr_pos.x() - rect.x())*127/rect.width();
				msgs << MDMA::EVENT_X;
			}
			if(active[MDMA::EVENT_Y] != MDMA::NOTHING)
			{
                signal[MDMA::EVENT_Y][MDMA::is_midi(active[MDMA::EVENT_Y])] = (rect.y() + rect.height() - main.curr_pos.y())*127/rect.height();
				msgs << MDMA::EVENT_Y;
			}
			*/
			break;
		}
		case MDMA::PAD:
		{
            QRect rect(P1,P2);
			if(rect.contains(main.curr_pos) && !rect.contains(main.last_pos) && active[MDMA::ENTER] != MDMA::NOTHING)
			{
				is_active[main.id] = true;
				msgs << MDMA::ENTER;
			}
			if(!rect.contains(main.curr_pos) && rect.contains(main.last_pos) && active[MDMA::EXIT] != MDMA::NOTHING)
			{
				is_active[main.id] = true;
				msgs << MDMA::EXIT;
			}
			if(rect.contains(main.curr_pos) && main.curr_open && !main.last_open && active[MDMA::OPEN] != MDMA::NOTHING)
			{
				is_active[main.id] = true;
				msgs << MDMA::OPEN;
			}
			if(rect.contains(main.curr_pos) && !main.curr_open && main.last_open && active[MDMA::OPEN] != MDMA::NOTHING)
			{
				is_active[main.id] = true;
				msgs << MDMA::CLOSE;
			}

			if(rect.contains(main.curr_pos) && rect.contains(main.last_pos) && active[MDMA::SHOCK] != MDMA::NOTHING)
			{
				/*
				int spe_chang = main.curr_speed.x() * main.last_speed.x() - main.curr_speed.y() * main.last_speed.y();
				int acc_value = main.curr_acc.x() * main.curr_acc.x() + main.curr_acc.y() * main.curr_acc.y();
				*/
				int shock = main.curr_acc.x() * main.last_speed.x() + main.curr_acc.y() * main.last_speed.y();

				//qDebug() << spe_chang << acc_value << shock;

				if(/*acc_value > 80 && spe_chang < 0*/ shock < -1200)
				{
					is_active[main.id] = true;
					msgs << MDMA::SHOCK;
				}
			}
/*
			if(!rect.contains(main.curr_pos))
			{
				if(hand_in[main.id] && active[MDMA::EXIT] != MDMA::NOTHING)
					msgs << MDMA::EXIT;
				hand_in[main.id] = false;
			}
			else
			{
				if(!hand_in[main.id])
				{
					if(active[MDMA::ENTER] != MDMA::NOTHING)
						msgs << MDMA::ENTER;
					hand_open[main.id] = main.open;
					hand_in[main.id] = true;
				}
				else
				{
					if(!hand_open[main.id] && main.open)
					{
						if(active[MDMA::OPEN] != MDMA::NOTHING)
							msgs << MDMA::OPEN;
						hand_open[main.id] = true;
					}
					if(hand_open[main.id] && !main.open)
					{
						if(active[MDMA::CLOSE] != MDMA::NOTHING)
							msgs << MDMA::CLOSE;
							hand_open[main.id] = false;
					}
				}
			}
			*/
			break;
		}
		case MDMA::SEGMENT:
		{
			QLineF vect_hand = QLineF(QPointF(main.curr_pos),QPointF(main.last_pos));
			QLineF vect_segm = QLineF(QPointF(P1), QPointF(P2));
			QPointF intersect_point;
			if(vect_segm.intersect(vect_hand, &intersect_point) == QLineF::BoundedIntersection)
			{
				if(vect_segm.dx() * vect_hand.dy() - vect_segm.dy() * vect_hand.dx() > 0)
				{
					if(active[MDMA::IN] != MDMA::NOTHING)
					{
						is_active[main.id] = true;
						msgs << MDMA::IN;
					}
				}
				else
				{
					if(active[MDMA::OUT] != MDMA::NOTHING)
					{
						is_active[main.id] = true;
						msgs << MDMA::OUT;
					}
				}
			}
		}
	}
	emph_display = is_active[0] || is_active[1] || is_active[2];
	return msgs;
}

// ============================================================================================

void EventZone::initEventZone ()
{
	qRegisterMetaTypeStreamOperators<EventZone>("EventZone");
	qMetaTypeId<EventZone>();
}

QDataStream& operator << (QDataStream& out, const EventZone& evz)
{
	out << evz.name								// QString
		<< evz.P1								// QPoint
		<< evz.P2								// QPoint
		<< evz.tab								// Int
		<< evz.type;							// Int (MDMA::type)
	for(int i = 0; i<9; i++)
	{
		out << evz.active[i]					// Int (MDMA::active)
			<< evz.signal[i][0]					// Char
			<< evz.signal[i][1]					// Char
			<< evz.signal[i][2];				// Char
	}
	out << evz.variable[0];
	out << evz.variable[1];

	return out;
}
QDataStream& operator >> (QDataStream& in, EventZone& evz)
{
	int tmp;
	in >> evz.name;								// QString
	in >> evz.P1;								// QPoint
	in >> evz.P2;								// QPoint
	in >> evz.tab;								// Int
	in >> tmp;
		evz.type = (MDMA::type) tmp;			// Int (MDMA::type)

	for(int i = 0; i<9; i++)
	{
		in >> tmp;
			evz.active[i] = (MDMA::active) tmp;	// Int (MDMA::active)
		in >> evz.signal[i][0];					// Char
		in >> evz.signal[i][1];					// Char
		in >> evz.signal[i][2];					// Char
	}
	in >> evz.variable[0];
	in >> evz.variable[1];

	return in;
}
