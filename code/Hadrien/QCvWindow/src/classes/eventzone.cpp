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
	for(int i=0; i<7; i++)
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
	for(int i=0; i<7; i++)
	{
		switch((MDMA::event)i)
		{
			case MDMA::EVENT_X:
			case MDMA::EVENT_Y:
				active[i] = MDMA::NOTHING;
				signal[i][0] = 0;
				signal[i][1] = 0;
				signal[i][2] = 196;
				break;
			case MDMA::ENTER:
			case MDMA::EXIT:
			case MDMA::OPEN:
			case MDMA::CLOSE:
			case MDMA::SHOCK:
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
			painter.fillRect(QRect(P1, P2), MDMA::type_to_color(type));

			painter.setPen(MDMA::text_color);
			painter.drawText(std::min(P1.x(), P2.x())+2, std::min(P1.y(), P2.y())+10, name);
			break;
		case MDMA::PAD :
			painter.fillRect(QRect(P1, P2), MDMA::type_to_color(type));

			painter.setPen(MDMA::text_color);
			painter.drawText(std::min(P1.x(), P2.x())+2, std::min(P1.y(), P2.y())+10, name);
			break;
		case MDMA::SEGMENT :
			painter.setPen(QPen(QBrush(MDMA::type_to_color(type)), 4, Qt::SolidLine, Qt::RoundCap));
			painter.drawLine(P1, P2);

			painter.setPen(MDMA::text_color);
			painter.drawText((P1.y()<P2.y() || P1.x()<P2.x())?P1:P2, name);
			break;
	}
}

