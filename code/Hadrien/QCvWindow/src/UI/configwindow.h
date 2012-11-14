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
		ConfigWindow(midiManager& _midi, configuration& _config, QWidget *parent = 0);
		~ConfigWindow();
		
	private slots:
		void on_pushButton_midi_clicked();

	private:
		void refreshPorts();

		Ui::ConfigWindow *ui;
		midiManager& midi;
		configuration& config;
};

#endif // CONFIGWINDOW_H
