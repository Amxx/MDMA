#include "zonemanager.h"
#include "ui_mainwindow.h"

ZoneManager::ZoneManager(Configuration& _config, QObject *parent) :
	QObject(parent),
	QPainter(),
	config(_config),
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

		EventZone evz(P1, P2, config.data.current_tab);
		ZoneEditor popup(evz);
		if(popup.exec())
		{
			if(config.data.zones.find(evz.name) != config.data.zones.end())
			{
				int i = 0;
				while(config.data.zones.find(evz.name+"_"+QString::number(i)) != config.data.zones.end()) i++;
				evz.name+=("_"+QString::number(i));
			}
			config.data.zones.insert(evz.name, evz);
			config.ui->treeWidget_list->addTopLevelItem(new QTreeWidgetItem(QStringList() << evz.name << MDMA::type_to_string(evz.type) << QString::number(evz.tab+1)));
			config.changed = true;
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

	if(config.freeze)
	{
		setPen(MDMA::text_color);
		fillRect(QRect(5, 5, 150, 30), MDMA::mask_color);
		drawText(QRect(5, 5, 150, 30), Qt::AlignCenter, "Display Freezed");
	}

	config.displayMask(*this);

	switch(config.calibration_status)
	{
		case MDMA::NOT_CALIBRATED:
		case MDMA::CALIBRATED:
			for(EventZone& evz : config.data.zones.values())
				if(evz.tab == config.data.current_tab) evz.display(*this);
			break;

		case MDMA::MASK_DRAW:
			break;

		case MDMA::HANDS_CLOSED:
		{	QPolygon poly_left;
			QPolygon poly_right;
			for(QPoint p : MDMA::zone_leftclose) poly_left << p;
			for(QPoint p : MDMA::zone_rightclose) poly_right << p;
			drawPolygon(poly_left);
			drawPolygon(poly_right);
//			fillRect(40, 200, 100, 100, MDMA::calib_color);
//			fillRect(500, 200, 100, 100, MDMA::calib_color);
			break;
		}
		case MDMA::HANDS_OPEN:
		{	QPolygon poly_left;
			QPolygon poly_right;
			for(QPoint p : MDMA::zone_leftopen) poly_left << p;
			for(QPoint p : MDMA::zone_rightopen) poly_right << p;
			drawPolygon(poly_left);
			drawPolygon(poly_right);
//			fillRect(40, 200, 100, 100, MDMA::calib_color);
//			fillRect(500, 200, 100, 100, MDMA::calib_color);
			break;
		}
	}

	config.ui->label_zone->setPixmap(pixmax);
}
