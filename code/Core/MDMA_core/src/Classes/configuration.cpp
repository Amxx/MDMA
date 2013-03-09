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
	qDebug() << size() << "zone(s) in configuration";
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

/*
 * ##################################################################################
 * #									ZONE										#
 * ##################################################################################
 */


bool Configuration::reset()
{
/*   if(_edit)
	   switch(QMessageBox::question(this, "Changed have been made to the configuration", "Would you like to save changes made to \""+data.name+"\" before closing ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
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
*/
	qDebug() << "reset";
	clear();
   _file = "";
   _tab = 0;
   _edit = false;
   return true;
}
/*
bool Core::load()
{
   if(_edit)
	   switch(QMessageBox::question(this, "Changed have been made to the configuration", "Would you like to save changes made to \""+data.name+"\" before closing ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
	   {
		   case QMessageBox::Save:
			   if(!save()) return false;
			   break;
		   case QMessageBox::Discard:
			   break;
		   default:
			   return false;
			   break;
	   }
	   QString open_path = QFileDialog::getOpenFileName(0, "Open file", QDir::homePath(), "MDMA configuration (*.mdma);;All file (*)", 0, 0); //QFileDialog::DontUseNativeDialog);
	   if(open_path == "") return false;

	   Zone::initSubConfig();
	   //QSettings file(open_path, QSettings::IniFormat);
	   //cfg = file.value("Config", qVariantFromValue(Configuration())).value<Configuration>();

	   ui->treeWidget_list->clear();
	   changed = false;

	   if(data.version != MDMA::VERSION)
	   {
		   QMessageBox::information(0, "Depreciated configuration file", "The configuration you tried to load does not match the current verion of MDMA");
		   reset();
		   return false;
	   }

	   for(EventZone& evz : data.zones)
		   ui->treeWidget_list->addTopLevelItem(new QTreeWidgetItem(QStringList() << evz.name << MDMA::type_to_string(evz.type) << QString::number(evz.tab+1)));
	   ui->comboBox_tab->setCurrentIndex(data.current_tab);


	   return true;
}
bool Core::save()
{
   qDebug() << "save";
}
bool Core::saveas()
{
   qDebug() << "saveas";
}
*/


/*
 * ##################################################################################
 * #									SLOTS										#
 * ##################################################################################
 */

void Configuration::edited()
{
	_edit = true;
}






void Configuration::initZone ()
{
	qRegisterMetaTypeStreamOperators<Configuration>("Configuration");
	qMetaTypeId<Configuration>();
}

QDataStream& operator << (QDataStream& out, const Configuration&)
{
	/*
	out << (int) z->_type						// int (MDMA::type)
		<< z->_name								// QString
		<< z->_geo								// QRect
		<< z->_tab								// int
		<< z->_active							// bool
		<< z->size();							// int
	for(MDMA::event s : z->keys())
		out << s << z->value(s);
	*/
	return out;
}
QDataStream& operator >> (QDataStream& in, Configuration&)
{
	/*
	int t;
	in >> t;									// int (MDMA::type)
	z->_type = (MDMA::type) t;
	in >> z->_name;								// QString
	in >> z->_geo;								// QRect
	in >> z->_tab;								// int
	in >> z->_active;							// bool
	in >> t;									// int
	for(int i = 0; i < t; ++i)
	{
		int k;
		Signal s;
		in >> k;
		in >> s;
		z->insert((MDMA::event) k, s);
	}
	*/
	return in;
}
