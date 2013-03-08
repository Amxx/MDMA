#include "configuration.h"

#include <QDebug>

Configuration::Configuration() :
	_file(""),
	_tab(0)
{
}
Configuration::~Configuration()
{
	for(Zone* z : *this)
		delete z;
}



void Configuration::Reset()
{
	for(Zone* z : *this) delete z;
	_file = "";
	_tab = 0;
}
void Configuration::Load()
{

}
void Configuration::Save()
{

}
void Configuration::Saveas()
{

}



void Configuration::add(Zone* z)
{
	if(!contains(z->_name))
	{
		insert(z->_name, z);
	}
	else
	{
		int i = 0;
		while(contains(z->_name + "_" + QString::number(i))) ++i;
		z->_name += "_" + QString::number(i);
		insert(z->_name, z);
	}
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
