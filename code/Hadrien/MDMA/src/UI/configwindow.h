#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <string>

#include <QDialog>
#include <QInputDialog>
#include <QString>

#include "../objects/configuration.h"
#include "../objects/midimanager.h"

namespace Ui {
	class ConfigWindow;
}

class ConfigWindow : public QDialog
{
		Q_OBJECT
		
	public:
		ConfigWindow(MidiManager& _midi, QWidget *parent = 0);
		~ConfigWindow();
		void closeEvent();
		
	private slots:
		void on_pushButton_midi_clicked();
		void on_pushButton_midi_refresh_clicked();
		void on_comboBox_midi_currentIndexChanged(int index);

		void on_checkBox_flip_clicked();

		void on_pushButton_ok_clicked();
		void on_pushButton_device_clicked();
		void on_pushButton_hand_track_clicked();
		void on_pushButton_mouse_track_clicked();



	private:
		bool refreshing;
		MidiManager& midi;
		Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
