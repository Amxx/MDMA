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
				int x_value = x_min + (x_max - x_min) * signal[MDMA::EVENT_X][MDMA::is_midi(active[MDMA::EVENT_X])]/127;
				painter.drawLine(QPoint(x_value, P1.y()), QPoint(x_value, P2.y()));
			}
			if(MDMA::is_midi(active[MDMA::EVENT_Y]))
			{
				int y_min = std::min(P1.y(), P2.y());
				int y_max = std::max(P1.y(), P2.y());
				int y_value = y_max - (y_max - y_min) * signal[MDMA::EVENT_Y][MDMA::is_midi(active[MDMA::EVENT_Y])]/127;
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
			midi_signal[0] = active[ev] << 8 & signal[ev][0];
			midi_signal[1] = 0x80 & signal[ev][1];
			midi_signal[2] = 0x80 & signal[ev][2];
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
	switch(type)
	{
		case MDMA::FADER:
		{
			QRect rect(P1,P2);
            rect = rect.normalized();

			if(rect.contains(main.curr_pos) && !main.open)
			{
				qDebug() << (main.curr_pos.x() - rect.x())*127/rect.width() << (rect.y() + rect.height() - main.curr_pos.y())*127/rect.height();


				if(active[MDMA::EVENT_X] != MDMA::NOTHING)
				{
					signal[MDMA::EVENT_X][MDMA::is_midi(active[MDMA::EVENT_X])] = (main.curr_pos.x() - rect.x())*127/rect.width();
					//msgs << MDMA::EVENT_X;
				}
				if(active[MDMA::EVENT_Y] != MDMA::NOTHING)
				{
					signal[MDMA::EVENT_Y][MDMA::is_midi(active[MDMA::EVENT_Y])] = (rect.y() + rect.height() - main.curr_pos.y())*127/rect.height();
					//msgs << MDMA::EVENT_Y;
				}
			}
			break;
/*
            if(!rect.contains(main.curr_pos))
            {
				is_active[main.hand] = false;
				hand_in[main.hand] = false;
				hand_open[main.hand] = false;
            }
            else
            {
				if(main.open)
                {
					hand_open[main.hand] = true;
					is_active[main.hand] = false;
                }
				else if(hand_in[main.hand] && hand_open[main.hand] && !main.open)
                {
					hand_open[main.hand] = false;
					is_active[main.hand] = true;
                }
				hand_in[main.hand] = true;
            }

			if(!is_active[main.hand]) break;

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
		}
		case MDMA::PAD:
		{
            QRect rect(P1,P2);

            if(!rect.contains(main.curr_pos))
            {
				if(hand_in[main.hand] && active[MDMA::EXIT] != MDMA::NOTHING)
                    msgs << MDMA::EXIT;
				hand_in[main.hand] = false;
            }
            else
            {
				if(!hand_in[main.hand])
                {
                    if(active[MDMA::ENTER] != MDMA::NOTHING)
                        msgs << MDMA::ENTER;
					hand_open[main.hand] = main.open;
					hand_in[main.hand] = true;
                }
                else
                {
					if(!hand_open[main.hand] && main.open)
                    {
                        if(active[MDMA::OPEN] != MDMA::NOTHING)
                            msgs << MDMA::OPEN;
						hand_open[main.hand] = true;
                    }
					if(hand_open[main.hand] && !main.open)
                    {
                        if(active[MDMA::CLOSE] != MDMA::NOTHING)
                            msgs << MDMA::CLOSE;
							hand_open[main.hand] = false;
                    }
                }
            }
			break;
		}
		case MDMA::SEGMENT:
		{
			is_active[main.hand] = false;
			QLineF vect_hand = QLineF(QPointF(main.curr_pos),QPointF(main.last_pos));
			QLineF vect_segm = QLineF(QPointF(P1), QPointF(P2));
			QPointF intersect_point;
			if(vect_segm.intersect(vect_hand, &intersect_point) == QLineF::BoundedIntersection)
			{
				is_active[main.hand] = true;
				if(vect_segm.dx() * vect_hand.dy() - vect_segm.dy() * vect_hand.dx() > 0)
					msgs << MDMA::IN;
				else
					msgs << MDMA::OUT;
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
	return in;
}
