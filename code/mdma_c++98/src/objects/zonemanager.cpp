#include "zonemanager.h"
#include "ui_mainwindow.h"
#include "ui_secondwindow.h"

ZoneManager::ZoneManager(QObject *parent) :
	QObject(parent),
	QPainter(),
	pixmax(640,480),
	P1(-1, -1),
	P2(-1, -1)
{
	pixmax.fill(Qt::transparent);
	begin(&pixmax);
	startTimer(40);
}


ZoneManager::~ZoneManager()
{
	end();
}


void ZoneManager::timerEvent(QTimerEvent*)
{
	display();
}

// ======================================================================

void ZoneManager::set_zone(QPoint pointer)
{
	if(P1.x() == -1)
	{
		P1 = pointer;
	}
	else
	{
		P2 = pointer;

		EventZone evz(P1, P2, Configuration::config().data.current_tab);
		ZoneEditor popup(evz);
		if(popup.exec())
		{
			if(Configuration::config().data.zones.find(evz.name) != Configuration::config().data.zones.end())
			{
				int i = 0;
				while(Configuration::config().data.zones.find(evz.name+"_"+QString::number(i)) != Configuration::config().data.zones.end()) i++;
				evz.name+=("_"+QString::number(i));
			}
			Configuration::config().data.zones.insert(evz.name, evz);
			Configuration::config().ui->treeWidget_list->addTopLevelItem(new QTreeWidgetItem(QStringList() << evz.name << MDMA::type_to_string(evz.type) << QString::number(evz.tab+1)));
			Configuration::config().changed = true;
		}
		reset_clic();
	}
}

void ZoneManager::reset_clic()
{
	P1 = QPoint(-1, -1);
	P2 = QPoint(-1, -1);
}

// ======================================================================

void ZoneManager::display()
{
	pixmax.fill(Qt::transparent);

	if(P1.x() != -1)
	{
		if(P2.x() != -1)
			fillRect(QRect(P1, P2), MDMA::temp_color);
		else
		{
			setPen(MDMA::temp_color);
			drawLine(P1.x()-3, P1.y(), P1.x()+3, P1.y());
			drawLine(P1.x(), P1.y()-3, P1.x(), P1.y()+3);
		}
	}

	if(Configuration::config().freeze)
	{
		setPen(MDMA::text_color);
		fillRect(QRect(5, 5, 150, 30), MDMA::mask_color);
		drawText(QRect(5, 5, 150, 30), Qt::AlignCenter, "Display Freezed");
	}

    Configuration::config().displayMask(*this);

    switch(Configuration::config().camera_manager.isCalibrated())
	{
		case MDMA::NOT_CALIBRATED:
		case MDMA::CALIBRATED:
            for(QMap<QString, EventZone>::Iterator it = Configuration::config().data.zones.begin() ; it != Configuration::config().data.zones.end() ; ++it)
                if(it->tab == Configuration::config().data.current_tab) it->display(*this);
			break;

        case MDMA::HANDS_CLOSED:
        {	QPolygon poly_left;
            QPolygon poly_right;
            for(QList<QPoint>::ConstIterator it = MDMA::zone_leftclose.begin() ; it != MDMA::zone_leftclose.end() ; ++it) poly_left << *it;
            for(QList<QPoint>::ConstIterator it = MDMA::zone_rightclose.begin() ; it != MDMA::zone_rightclose.end() ; ++it) poly_right << *it;
            drawPolygon(poly_left);
            drawPolygon(poly_right);
            break;
        }
        case MDMA::HANDS_OPEN:
		{	QPolygon poly_left;
			QPolygon poly_right;
            for(QList<QPoint>::ConstIterator it = MDMA::zone_leftopen.begin() ; it != MDMA::zone_leftopen.end() ; ++it) poly_left << *it;
            for(QList<QPoint>::ConstIterator it = MDMA::zone_rightopen.begin() ; it != MDMA::zone_rightopen.end() ; ++it) poly_right << *it;
            drawPolygon(poly_left);
            drawPolygon(poly_right);
            break;
		}
        case MDMA::MASK_DRAW:
            break;
	}

	Configuration::config().ui->label_zone->setPixmap(pixmax);

	if(Configuration::config().second_display)
		Configuration::config().second_display->label_zones->setPixmap(Configuration::config().flip_display?QPixmap::fromImage(pixmax.toImage().mirrored(true, false)): pixmax);

}
