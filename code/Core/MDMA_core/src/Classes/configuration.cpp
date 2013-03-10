#include "configuration.h"

#include <QDebug>

Configuration::Configuration() :
	_file(""),
	_tab(0),
	_edit(false)
{
}

Configuration::Configuration(const Configuration &cpy) :
	QObject(cpy.parent()),
	QList<Zone>(cpy),
	_file(cpy._file),
	_tab(cpy._tab),
	_edit(cpy._edit)
{
}

Configuration::~Configuration()
{
}

/*
 * ##################################################################################
 * #									ACCESS										#
 * ##################################################################################
 */

Zone& Configuration::insertZone(Zone& z)
{
	push_back(z);
	return last();
}

void Configuration::removeZone(Zone& z)
{
	removeOne(z);
}

void Configuration::setTab(int t)
{
	_tab  = t;
	emit tabChanged(t);
}
int Configuration::getTab()
{
	return _tab;
}

void Configuration::edited(bool e)
{
	_edit = e;
}

bool Configuration::isEdited()
{
	return _edit;
}


/*
 * ##################################################################################
 * #								CONFIG MANAGEMENT								#
 * ##################################################################################
*/

bool Configuration::reset()
{
	if(_edit)
		switch(QMessageBox::question(0, "Changed have been made to the configuration", "Would you like to save changes ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
		{
			case QMessageBox::Save:
				if(!save()) return false;
				break;
			case QMessageBox::Discard:
				break;
			case QMessageBox::Cancel:
				return false;
				break;
			default:
				break;
		}
	clear();
	_file = "";
	_tab = 0;
	_edit = false;
	return true;
}

bool Configuration::load()
{
	if(reset())
	{
		_file = QFileDialog::getOpenFileName(0, "Open file", QDir::homePath(), "MDMA configuration (*.mdma);;All file (*)", 0, 0);
		if(_file == "") return false;
		QFile file(_file);
		file.open(QIODevice::ReadOnly);
		QDataStream in(&file);
		in >> (*this);
		file.close();
		emit reconstruct();
		return true;
	}
	return false;
}

bool Configuration::save()
{
	if(_file == "")
	{
		_file = QFileDialog::getSaveFileName(0, "Save file", QDir::homePath()+"/new_config.mdma", "MDMA configuration (*.mdma);;All file (*)", 0, 0);
		if(_file == "") return false;
	}
	QFile file(_file);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	out << (*this);
	file.close();
	_edit = false;
	return true;
}
bool Configuration::saveas()
{
	QString new_path = QFileDialog::getSaveFileName(0, "Save file as", (_file == "")?(QDir::homePath()+"/new_config.mdma"):_file, "MDMA configuration (*.mdma);;All file (*)", 0, 0);
	if(new_path == "") return false;

	_file = new_path;
	save();
	return true;
}





QDataStream& operator << (QDataStream& out, const Configuration& c)
{
	out << (QList<Zone>) c;
	return out;
}
QDataStream& operator >> (QDataStream& in, Configuration& c)
{
	QList<Zone> l;
	in >> l;
	c << l;
	return in;
}

