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
		void on_checkBox_flip_clicked();
		void on_pushButton_ok_clicked();

	private:
		void refreshPorts();

		MidiManager& midi;
		Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
