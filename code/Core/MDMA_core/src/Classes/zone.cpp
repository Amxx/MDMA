#include "zone.h"

#include <QDebug>

/*
 * ##################################################################################
 * #									SIGNAL										#
 * ##################################################################################
 */

Signal::Signal() :
	type(MDMA::NOTHING),
	variable(2)
{
	signal[0] = 0;
	signal[1] = 0;
	signal[2] = 0;
}

void Signal::initSignal ()
{
	qRegisterMetaTypeStreamOperators<Signal>("Signal");
	qMetaTypeId<Signal>();
}
QDataStream& operator << (QDataStream& out, const Signal& s)
{
	out << (int) s.type							// int (MDMA::signal)
		<< s.signal[0]							// int
		<< s.signal[1]							// int
		<< s.signal[2]							// int
		<< s.variable;							// int
	return out;
}
QDataStream& operator >> (QDataStream& in, Signal& s)
{
	int t;
	in >> t;									// int (MDMA::signal)
		s.type = (MDMA::signal) t;
	in >> s.signal[0];							// int
	in >> s.signal[1];							// int
	in >> s.signal[2];							// int
	in >> s.variable;							// int
	return in;
}

/*
 * ##################################################################################
 * #									ZONE										#
 * ##################################################################################
 */

Zone::Zone() :
	_type(MDMA::NONE),
	_name("New Zone"),
	_geo(),
	_tab(0),
	_active(false)
{
}
Zone::Zone(QRect r, int t) :
	_type(MDMA::NONE),
	_name("New Zone"),
	_geo(r),
	_tab(t),
	_active(false)
{
}
Zone::Zone(const Zone& cpy) :
	QObject(cpy.parent()),
	QMap<MDMA::event, Signal>(cpy),
	_type(cpy._type),
	_name(cpy._name),
	_geo(cpy._geo),
	_tab(cpy._tab),
	_active(cpy._active)
{
}
Zone::~Zone()
{
	emit deleted();
}

/*
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
*/

QList<Signal> Zone::update(QMap<int,Pointer>& pts)
{
	QList<Signal> msgs;
	_active = false;
	for(Pointer& pt : pts)
		switch(_type)
		{
			/*
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

		//
		//			implementer la frappe !!!!
		//

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
			*/
			default:
				break;
		}
	emit updated();
	return msgs;
}

void Zone::initZone ()
{
	qRegisterMetaTypeStreamOperators<Zone>("Zone");
	qMetaTypeId<Zone>();
}

QDataStream& operator << (QDataStream& out, const Zone& z)
{
	out << (int) z._type						// int (MDMA::type)
		<< z._name								// QString
		<< z._geo								// QRect
		<< z._tab								// int
		<< z._active							// bool
		<< z.size();							// int
//	for(MDMA::event s : z.keys())
//		out << s << z.value(s);
	return out;
}
QDataStream& operator >> (QDataStream& in, Zone& z)
{
	int t;
	in >> t;									// int (MDMA::type)
		z._type = (MDMA::type) t;
	in >> z._name;								// QString
	in >> z._geo;								// QRect
	in >> z._tab;								// int
	in >> z._active;							// bool
	in >> t;									// int
//	for(int i = 0; i < t; ++i)
//	{
//		int k;
//		Signal s;
//		in >> k;
//		in >> s;
//		z.insert((MDMA::event) k, s);
//	}
	return in;
}
