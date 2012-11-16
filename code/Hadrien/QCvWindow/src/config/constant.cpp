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


QColor MDMA::type_to_border_color(MDMA::type t, bool /*emph*/, bool alpha)
{
	switch(t)
	{
		case FADER:
			return QColor(255, 0, 0, (alpha)?128:255);
		case PAD:
			return QColor(78, 98, 255, (alpha)?128:255);
		case SEGMENT:
			return QColor(78, 167, 255, (alpha)?128:255);
	}
	return QColor();
}

QColor MDMA::type_to_fill_color(MDMA::type t, bool /*emph*/, bool alpha)
{
	switch(t)
	{
		case FADER:
			return QColor(167, 78, 255, (alpha)?128:255);
		case PAD:
			return QColor(78, 98, 255, (alpha)?128:255);
		case SEGMENT:
			return QColor(78, 167, 255, (alpha)?128:255);
	}
	return QColor();
}

int MDMA::is_midi(MDMA::active s)
{
	switch(s)
	{
		case MDMA::NOTE_OFF:
		case MDMA::NOTE_ON:
		case MDMA::POLYFONIC_AFTERTOUCH:
		case MDMA::CONTROL_CHANGE:
			return 2;
		case MDMA::PROGRAM_CHANGE:
		case MDMA::CHANNEL_AFTERTOUCH:
			return 1;
		case MDMA::PITCH_BENDING:
			return 2;
		case MDMA::NOTHING:
		case MDMA::GOTO_TAB1:
		case MDMA::GOTO_TAB2:
		case MDMA::GOTO_TAB3:
			return 0;
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
//			qDebug() << value;
			return value.contains("GNOME", Qt::CaseInsensitive);
		}
	return false;
}
