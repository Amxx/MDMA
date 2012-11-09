#include "constant.h"


QString MDMA::type_to_string(MDMA::type t)
{
	switch(t)
	{
		case FADER : return "Fader";
		case PAD : return "Pad";
		case SEGMENT : return "Segment";
	}
	return "";
}


QColor MDMA::type_to_color(MDMA::type t)
{
	switch(t)
	{
		case FADER:
			return QColor(167, 78, 255, 128);
		case PAD:
			return QColor(78, 98, 255, 128);
		case SEGMENT:
			return QColor(78, 167, 255, 128);
	}
	return QColor();
}

bool MDMA::is_midi(MDMA::active s)
{
	switch(s)
	{
		case MDMA::NOTE_OFF:
		case MDMA::NOTE_ON:
		case MDMA::POLYFONIC_AFTERTOUCH:
		case MDMA::CHANNEL_PRESSURE:
		case MDMA::PROGRAM_CHANGE:
		case MDMA::CONTROL_CHANGE:
		case MDMA::PITCH_BENDING:
		case MDMA::SYSTEM:
			return true;
		case MDMA::NOTHING:
		case MDMA::GOTO_TAB1:
		case MDMA::GOTO_TAB2:
		case MDMA::GOTO_TAB3:
			return false;
	}
	return false;
}

bool usesGnome()
{
	QString prefix("DESKTOP_SESSION=");
	foreach(QString env, QProcess::systemEnvironment())
		if (env.startsWith(prefix))
		{
			QString value = env.mid(prefix.length());
			qDebug() << value;
			return value.contains("GNOME", Qt::CaseInsensitive);
		}
	return false;
}
