#include "subconfig.h"

SubConfig::SubConfig() :
	version(MDMA::VERSION),
	name("New Configuration"),
	path(""),
	current_tab(0)
{
}

SubConfig::SubConfig(const SubConfig &sub_config) :
	version(sub_config.version),
	name(sub_config.name),
	path(sub_config.path),
	current_tab(sub_config.current_tab),
	zones(sub_config.zones)
{
}

SubConfig::~SubConfig()
{
}



void SubConfig::initSubConfig()
{
	qRegisterMetaTypeStreamOperators<SubConfig>("SubConfig");
	qMetaTypeId<SubConfig>();
}

QDataStream& operator << (QDataStream& out, const SubConfig& sub_config)
{

	out << sub_config.version
		<< sub_config.name							// QString
		<< sub_config.path							// QString
		<< sub_config.current_tab					// Int
		<< sub_config.zones;

	return out;
}
QDataStream& operator >> (QDataStream& in, SubConfig& sub_config)
{
	in >> sub_config.version;
	in >> sub_config.name;							// QString
	in >> sub_config.path;							// QPoint
	in >> sub_config.current_tab;					// QPoint
	in >> sub_config.zones;

	return in;
}

