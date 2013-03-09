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
 * #									SLOTS										#
 * ##################################################################################
 */

void Configuration::edited()
{
	_edit = true;
}










void Configuration::initConfiguration ()
{
	qRegisterMetaTypeStreamOperators<Configuration>("Configuration");
	qMetaTypeId<Configuration>();
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
