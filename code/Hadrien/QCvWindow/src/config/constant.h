#ifndef CONSTANT_H
#define CONSTANT_H

#include <QColor>
#include <QDebug>
#include <QFileDialog>
#include <QProcess>
#include <QString>

namespace MDMA
{
	enum type
	{
		FADER,
		PAD,
		SEGMENT
	};
	enum event
	{
		EVENT_X,
		EVENT_Y,
		ENTER,
		EXIT,
		OPEN,
		CLOSE,
		SHOCK
	};
	enum active
	{
		NOTE_OFF,
		NOTE_ON,
		POLYFONIC_AFTERTOUCH,
		CHANNEL_PRESSURE,
		PROGRAM_CHANGE,
		CONTROL_CHANGE,
		PITCH_BENDING,
		SYSTEM,
		GOTO_TAB1,
		GOTO_TAB2,
		GOTO_TAB3,
		NOTHING
	};
	enum calibration
	{
		NOT_CALIBRATED,
		MASK_DRAW,
		HANDS_CLOSED,
		HANDS_OPEN,
		CALIBRATED
	};
	typedef unsigned char signal[3];

	const QColor temp_color = QColor(QColor(255, 255, 78, 128));
	const QColor text_color = Qt::white;

	QString type_to_string(type t);
	QColor type_to_color(type t);
	bool is_midi(active s);
}

bool usesGnome();
const QFileDialog::Options QFILEDIALOGOPTION = (usesGnome())?QFileDialog::DontUseNativeDialog:QFileDialog::Options(0);

#endif // CONSTANT_H
