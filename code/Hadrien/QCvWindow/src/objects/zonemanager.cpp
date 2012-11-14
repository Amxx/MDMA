#include "zonemanager.h"
#include "ui_mainwindow.h"

zoneManager::zoneManager(configuration& _config, QObject *parent) :
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


zoneManager::~zoneManager()
{
	end();
}


void zoneManager::timerEvent(QTimerEvent*)
{
	display();
}


void zoneManager::left_clic(QPoint pointer)
{
	switch(config.calibration_status)
	{
		case MDMA::NOT_CALIBRATED:
		case MDMA::CALIBRATED:
			set_zone(pointer);
			break;
		case MDMA::MASK_DRAW:
			config.user_mask.push_back(pointer);
			break;
		case MDMA::HANDS_CLOSED:
		case MDMA::HANDS_OPEN:
			//
			break;

	}
}

void zoneManager::right_clic(QPoint pointer)
{
	switch(config.calibration_status)
	{
		case MDMA::NOT_CALIBRATED:
		case MDMA::CALIBRATED:
			reset_clic();
			break;
		case MDMA::MASK_DRAW:
			config.user_mask.pop_back();
			break;
		case MDMA::HANDS_CLOSED:
		case MDMA::HANDS_OPEN:
			//
			break;

	}
}

// ======================================================================

void zoneManager::set_zone(QPoint pointer)
{
	if(P1.x() == -1)
	{
		P1 = pointer;
	}
	else
	{
		P2 = pointer;

		eventZone evz(P1, P2, config.current_tab);
		zoneEditor popup(evz);

		if(popup.exec())
		{
			if(config.zones.find(evz.name) != config.zones.end())
			{
				int i = 0;
				while(config.zones.find(evz.name+"_"+QString::number(i)) != config.zones.end()) i++;
				evz.name+=("_"+QString::number(i));
			}
			config.zones.insert(evz.name, evz);
			config.ui->treeWidget_list->addTopLevelItem(new QTreeWidgetItem(QStringList() << evz.name << MDMA::type_to_string(evz.type) << QString::number(evz.tab+1)));
			config.changed = true;
		}
		reset_clic();
	}
}

void zoneManager::reset_clic()
{
	P1 = QPoint(-1, -1);
	P2 = QPoint(-1, -1);
}

// ======================================================================

void zoneManager::display()
{
	pixmax.fill(Qt::transparent);
	if(P1.x() != -1)
	{
		if(P2.x() != -1)
		{
			fillRect(QRect(P1, P2), MDMA::temp_color);
		}
		else
		{
			setPen(MDMA::temp_color);
			drawLine(P1.x()-3, P1.y(), P1.x()+3, P1.y());
			drawLine(P1.x(), P1.y()-3, P1.x(), P1.y()+3);
		}
	}
	for(eventZone& evz : config.zones.values())
	{
		if(evz.tab == config.current_tab)
			evz.display(*this);
	}
	config.ui->label_zone->setPixmap(pixmax);
}
