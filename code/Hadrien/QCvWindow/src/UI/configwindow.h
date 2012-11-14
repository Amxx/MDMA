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
		ConfigWindow(MidiManager& _midi, Configuration& _config, QWidget *parent = 0);
		~ConfigWindow();
		void closeEvent(QCloseEvent* ev);
		
	private slots:
		void on_pushButton_cancel_clicked();
		void on_pushButton_next_clicked();

		void on_pushButton_midi_clicked();

	private:
		void refreshPorts();

		MidiManager& midi;
		Configuration& config;
		Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
