#include "zonedisplay.h"
#include "ui_mainwindow.h"

zoneDisplay::zoneDisplay(configuration* _config, QObject *parent) :
	QObject(parent),
	QPainter(),
	config(_config),
	cursor(QPoint(-1, -1))
{
	pixmax = new QPixmap(640, 480);
	pixmax->fill(Qt::transparent);
	begin(pixmax);
	startTimer(40);
}


zoneDisplay::~zoneDisplay()
{
	end();
	delete pixmax;
}


void zoneDisplay::timerEvent(QTimerEvent*)
{
	pixmax->fill(Qt::transparent);


	for(eventZone evz : config->zones.values())
	{
		if(evz.tab == config->current_tab())
		{
			QFont font;
			font.setPointSize(8);
			setFont(font);

			switch(evz.type)
			{
				case MDMA::FADER :
					setPen(Qt::green);
					drawRect(QRect(evz.P1, evz.P2));
					setPen(Qt::white);
					drawText(std::min(evz.P1.x(),evz.P2.x())+2, std::min(evz.P1.y(),evz.P2.y())+10, evz.name);
					break;
				case MDMA::PAD :
					setPen(Qt::blue);
					drawRect(QRect(evz.P1, evz.P2));
					setPen(Qt::white);
					drawText(std::min(evz.P1.x(),evz.P2.x())+2, std::min(evz.P1.y(),evz.P2.y())+10, evz.name);
					break;
				case MDMA::SEGMENT :
					setPen(Qt::yellow);
					drawLine(evz.P1, evz.P2);
					setPen(Qt::white);
					drawText((evz.P1.x()>evz.P2.y())?evz.P1:evz.P2, evz.name);
					break;
			}

		}
	}

	config->ui->label_zone->setPixmap(*pixmax);
}


void zoneDisplay::clic(QPoint pointer)
{
	if(cursor.x() < 0 || cursor.y() < 0)
	{
		cursor = pointer;
	}
	else
	{
		eventZone evz(cursor, pointer, config->current_tab());
		zoneEditor popup(&evz);

		if(popup.exec())
		{
			if(config->zones.find(evz.name) != config->zones.end())
			{
				int i = 0;
				while(config->zones.find(evz.name+"_"+QString::number(i)) != config->zones.end()) i++;
				evz.name+=("_"+QString::number(i));
			}
			config->zones.insert(evz.name, evz);

			config->ui->treeWidget_list->addTopLevelItem(new QTreeWidgetItem(QStringList() << evz.name << MDMA::type_to_string(evz.type) << QString::number(evz.tab+1)));
		}
		cursor = QPoint(-1, -1);
	}
}

void zoneDisplay::clear()
{
	//zones.clear();
}
