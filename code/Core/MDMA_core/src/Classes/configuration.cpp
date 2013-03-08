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
	clear();
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



void Configuration::setTab(int t)
{
	_tab  = t;
	emit tabChanged(t);
}
int Configuration::getTab()
{
	return _tab;
}
