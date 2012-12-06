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
		SHOCK,
		IN,
		OUT
	};
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
	enum calibration
	{
		NOT_CALIBRATED,
		MASK_DRAW,
		HANDS_CLOSED,
		HANDS_OPEN,
		CALIBRATED
	};
	enum tracking
	{
		LEFT,
		RIGHT,
		MOUSE
	};

	typedef unsigned char* signal;
    typedef QPair<active, signal> event_signal;


	const QColor calib_color =				QColor(64, 64, 64, 128);
	const QColor mask_color =				QColor(64, 64, 64, 128);
	const QColor temp_color =				QColor(255, 255, 78, 128);
	const QColor text_color =				Qt::white;

	const QList<QPoint> zone_leftopen =		QList<QPoint>() << QPoint(040, 050) << QPoint(240, 050) << QPoint(240, 250) << QPoint(040, 250);
	const QList<QPoint> zone_rightopen =	QList<QPoint>() << QPoint(400, 050) << QPoint(600, 050) << QPoint(600, 250) << QPoint(400, 250);
	const QList<QPoint> zone_leftclose =	QList<QPoint>() << QPoint(040, 050) << QPoint(240, 050) << QPoint(240, 250) << QPoint(040, 250);
	const QList<QPoint> zone_rightclose =	QList<QPoint>() << QPoint(400, 050) << QPoint(600, 050) << QPoint(600, 250) << QPoint(400, 250);


	QString type_to_string(type t);
	QColor type_to_border_color(type t, bool emph = false, bool alpha = true);
	QColor type_to_fill_color(type t, bool emph = false, bool alpha = true);

	int is_midi(active s);
}

bool usesGnome();
//const QFileDialog::Options QFILEDIALOGOPTION = (usesGnome())?QFileDialog::DontUseNativeDialog:QFileDialog::Options(0);
const QFileDialog::Options QFILEDIALOGOPTION(0);


#endif // CONSTANT_H
