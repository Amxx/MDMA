#include "define.h"
/*
int MDMA::isMidi(active a)
{
	int result = 0;
	switch(a)
	{
		case MDMA::NOTE_OFF:
		case MDMA::NOTE_ON:
		case MDMA::POLYFONIC_AFTERTOUCH:
		case MDMA::CONTROL_CHANGE:
			result = 2;
			break;
		case MDMA::PROGRAM_CHANGE:
		case MDMA::CHANNEL_AFTERTOUCH:
		case MDMA::PITCH_BENDING:
			result = 1;
			break;
		case MDMA::NOTHING:
		case MDMA::GOTO_TAB1:
		case MDMA::GOTO_TAB2:
		case MDMA::GOTO_TAB3:
			result = 0;
	}
	return result;
}


QString MDMA::typeToString(MDMA::type t)
{
	switch(t)
	{
		case FADER : return "Fader";
		case PAD : return "Pad";
		case SEGMENT : return "Segment";
	}
	return "";
}


QColor MDMA::typeToBorderColor(MDMA::type t, bool, bool alpha)
{
	switch(t)
	{
		case FADER:
			return QColor(255, 0, 0, alpha?128:255);
		case PAD:
			return QColor(78, 98, 255, alpha?128:255);
		case SEGMENT:
			return QColor(78, 167, 255, alpha?128:255);
	}
	return QColor();
}

QColor MDMA::typeToFillColor(MDMA::type t, bool emph, bool alpha)
{
	if(emph) return QColor(255, 128, 128, alpha?128:255);

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
*/
