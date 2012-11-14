#include "eventzone.h"

eventZone::eventZone()
{
}


eventZone::eventZone(const eventZone &cpy) :
	name(cpy.name),
	P1(cpy.P1),
	P2(cpy.P2),
	tab(cpy.tab),
	type(cpy.type)
{
	for(int i=0; i<9; i++)
	{
		active[i] = cpy.active[i];
		for(int j=0; j<3; j++)
			signal[i][j] = cpy.signal[i][j];
	}
}


eventZone::eventZone(QPoint _P1, QPoint _P2, int _tab) :
	name("New Zone"),
	P1(_P1),
	P2(_P2),
	tab(_tab),
	type(MDMA::FADER)
{
	for(int i=0; i<9; i++)
	{
		switch((MDMA::event)i)
		{
			case MDMA::EVENT_X:
			case MDMA::EVENT_Y:
			case MDMA::ENTER:
			case MDMA::EXIT:
			case MDMA::OPEN:
			case MDMA::CLOSE:
			case MDMA::SHOCK:
			case MDMA::IN:
			case MDMA::OUT:
				active[i] = MDMA::NOTHING;
				signal[i][0] = 0;
				signal[i][1] = 0;
				signal[i][2] = 0;
		}
	}
}

eventZone::~eventZone()
{
}


void eventZone::display(QPainter& painter)
{
	QFont font;
	font.setPointSize(8);
	painter.setFont(font);

	switch(type)
	{
		case MDMA::FADER :
		{
			painter.setPen(QPen(QBrush(MDMA::type_to_border_color(type)), 0, Qt::SolidLine, Qt::SquareCap));
			painter.drawRect(QRect(P1,P2));
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
			painter.setPen(QPen(QBrush(MDMA::type_to_border_color(type)), 0, Qt::SolidLine, Qt::SquareCap));
			painter.drawRect(QRect(P1,P2));
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

unsigned char* eventZone::getMidi(MDMA::event ev)
{
	unsigned char* midi_signal = new unsigned char[3];
	midi_signal[0] = active[ev] << 8 & signal[ev][0];
	midi_signal[1] = 0x80 & signal[ev][1];
	midi_signal[2] = 0x80 & signal[ev][2];
	return midi_signal;
}

unsigned char* eventZone::update(HandDescriptor &main)
{
    int d = 0, t;
    QPoint vec1, vec2;
    QPoint x;
    QRect rect(P1,P2);

    QList<unsigned char*> msg;
    if(valide)
    {
        switch(type)
        {
        case MDMA::FADER:
            if(main.ouvert < MAIN_OUVERTE && rect.contains(main.actuel))
            {
                signal[MDMA::EVENT_X][1] = (main.actuel.x - rect.x())*128/rect.width();
                signal[MDMA::EVENT_Y][1] = (main.actuel.y - rect.y())*128/rect.height();

                if(active[MDMA::EVENT_X] != MDMA::NOTHING) msg.push_back(getMidi(MDMA::EVENT_X));
                if(active[MDMA::EVENT_Y] != MDMA::NOTHING) msg.push_back(getMidi(MDMA::EVENT_Y));
                return true;
            }
            break;
        case MDMA::PAD:
            /*if(main.ouvert < MAIN_OUVERTE && main.actuel.inside(rect))
            {
                if(main.gauche && gauche_dedans)
                return true;
            }*/
            break;
        case MDMA::SEGMENT:
            //Intersection des deux segments, celui de la zone et celui de la main
            vec1 = main.actuel - main.precedent;
            vec2 = coin2 - coin1;
            //Calcul du dénominateur
            d = vec1.x() * vec2.y() - vec1.y() * vec2.x();
            if(d == 0)
                break;
            //Vérifie si l'intersection est dans le segment de la zone
            x = main.precedent - coin1;
            t = vec1.x() * x.y() - vec1.y() * x.x();
            if(d*t < 0 || abs(t) > abs(d))
                break;

            //Vérifie si l'intersection est dans le segment décrit par la main
            x = coin1 - main.precedent;
            t = vec2.x() * x.y() - vec2.y() * x.x();
            if(d*t < 0 || abs(t) > abs(d))
                break;

            msg.push_back(getMidi(MDMA::ENTER));
            break;
        }
    }
    return msg;
}
