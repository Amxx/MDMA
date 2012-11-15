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
	type(MDMA::FADER),
	is_active(false),
	hand_in(false),
	hand_open(false)
{
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
	type(cpy.type),
	is_active(false),
	hand_in(false),
	hand_open(false)
{
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


void EventZone::display(QPainter& painter)
{
	QFont font;
	font.setPointSize(8);
	painter.setFont(font);

	switch(type)
	{
		case MDMA::FADER :
		{
			//painter.setPen(QPen(QBrush(MDMA::type_to_border_color(type)), 0, Qt::SolidLine, Qt::SquareCap));
			//painter.drawRect(QRect(P1,P2));
			painter.fillRect(QRect(P1, P2), MDMA::type_to_fill_color(type));

			painter.setPen(QPen(QBrush(MDMA::type_to_border_color(type)), 3, Qt::SolidLine, Qt::SquareCap));
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
			//painter.setPen(QPen(QBrush(MDMA::type_to_border_color(type)), 0, Qt::SolidLine, Qt::SquareCap));
			//painter.drawRect(QRect(P1,P2));
			painter.fillRect(QRect(P1, P2), MDMA::type_to_fill_color(type));

			painter.setPen(MDMA::text_color);
			painter.drawText(std::min(P1.x(), P2.x())+2, std::min(P1.y(), P2.y())+10, name);
			break;
		}

		case MDMA::SEGMENT :
		{
			QPolygon poly;
			QPoint center, director;

			painter.setPen(QPen(QBrush(MDMA::type_to_fill_color(type)), 3, Qt::SolidLine, Qt::RoundCap));
			painter.drawLine(P1, P2);

			painter.setPen(QPen(QBrush(MDMA::type_to_fill_color(type)), 1, Qt::SolidLine, Qt::RoundCap));
			painter.setBrush(QBrush(MDMA::type_to_fill_color(type)));
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
	MDMA::signal midi_signal = new unsigned char[3];
	midi_signal[0] = active[ev] << 8 & signal[ev][0];
	midi_signal[1] = 0x80 & signal[ev][1];
	midi_signal[2] = 0x80 & signal[ev][2];
	return midi_signal;
}

QList<MDMA::signal> EventZone::update(HandDescriptor &main)
{
	QList<MDMA::signal> msgs;

	/*
	switch(type)
	{
		case MDMA::FADER:
		{
			QRect rect(P1,P2);


			//if(main.ouvert > MAIN_OUVERTE || !rect.contains(main.actuel))
			//	is_active = false;
			//if(main.ouvert < MAIN_OUVERTE && rect.contains(main.actuel))


			if(!is_active) break;

			if(active[MDMA::EVENT_X] != MDMA::NOTHING)
			{
				signal[MDMA::EVENT_X][MDMA::is_midi(active[MDMA::EVENT_X])] = (main.actuel.x - rect.x())*127/rect.width();
				msgs << getMidi(MDMA::EVENT_X);
			}
			if(active[MDMA::EVENT_Y] != MDMA::NOTHING)
			{
				signal[MDMA::EVENT_Y][MDMA::is_midi(active[MDMA::EVENT_Y])] = (rect.y() + rect.height() - main.actuel.y)*127/rect.height();
				msgs << getMidi(MDMA::EVENT_Y);
			}
			break;
		}
		case MDMA::PAD:
		{
			//if(main.ouvert < MAIN_OUVERTE && main.actuel.inside(rect))
			//{
			//	if(main.gauche && gauche_dedans)
			//	return true;
			//}
			break;
		}
		case MDMA::SEGMENT:
		{
			//Intersection des deux segments, celui de la zone et celui de la main
			QPoint vect_hand = main.actuel - main.precedent;
			QPoint vect_segm = P1 - P2;
			QPoint x;
			int d, t;

			//Calcul du dénominateur
			d = vect_hand.x() * vect_segm.y() - vect_hand.y() * vect_segm.x();

			if(d == 0) break;

			//Vérifie si l'intersection est dans le segment de la zone
			x = main.precedent - P1;
			t = vect_hand.x() * x.y() - vect_hand.y() * x.x();

			if(d*t < 0 || abs(t) > abs(d)) break;

			//Vérifie si l'intersection est dans le segment décrit par la main
			x = P1 - main.precedent;
			t = vect_segm.x() * x.y() - vect_segm.y() * x.x();

			if(d*t < 0 || abs(t) > abs(d)) break;
				if(d > 0)
				msgs << getMidi(MDMA::IN);
			else
				msgs << getMidi(MDMA::OUT);
			break;
		}
	}
	*/
	return msgs;
}
