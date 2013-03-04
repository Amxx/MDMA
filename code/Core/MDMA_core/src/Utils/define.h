#ifndef DEFINE_H
#define DEFINE_H

#include "QColor"
#include "QString"

#define appCore	Core::getCore

namespace MDMA
{
	typedef unsigned char* signal;

/*
 * ######################################################
 * #						GENERAL						#
 * ######################################################
 */
	enum exn
	{
		DEVICE_NOT_DETECTED
	};

	enum device
	{
		Kinect,
		Mouse,
		WebCam
	};

/*
 * ######################################################
 * #						MIDI						#
 * ######################################################
 */

	enum active
	{
		NOTE_OFF,
		NOTE_ON,
		POLYFONIC_AFTERTOUCH,
		CONTROL_CHANGE,
		PROGRAM_CHANGE,
		CHANNEL_AFTERTOUCH,
		PITCH_BENDING,
		GOTO_TAB1,
		GOTO_TAB2,
		GOTO_TAB3,
		NOTHING
	};

	int isMidi(active a);

/*
 * ######################################################
 * #						ZONES						#
 * ######################################################
 */

	enum event
	{
		EVENT_X,
		EVENT_Y,
		ENTER,
		EXIT,
		OPEN,
		CLOSE,
		SHOCK,
		IN,
		OUT
	};
	enum type
	{
		FADER,
		PAD,
		SEGMENT
	};

	const int SEUIL = 2;
	const QColor tempColor = QColor(255, 255, 78, 128);
	const QColor textColor = QColor(255, 255, 255, 255);

	QString typeToString(type t);
	QColor typeToBorderColor(type t, bool emph = false, bool alpha = true);
	QColor typeToFillColor(type t, bool emph = false, bool alpha = true);
}


#endif // DEFINE_H
