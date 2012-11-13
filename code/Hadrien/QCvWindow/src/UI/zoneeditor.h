#ifndef ZONEEDITOR_H
#define ZONEEDITOR_H

#include <QDialog>
#include <QPoint>

#include "../objects/configuration.h"

namespace Ui {
	class zoneEditor;
}

class zoneEditor : public QDialog
{
		Q_OBJECT
		
	public:
		explicit zoneEditor(eventZone& _evz, QWidget* parent = 0);
		~zoneEditor();
		
	protected:
		void init();

	private slots:
		void on_buttonBox_accepted();

		void on_comboBox_axex_0_currentIndexChanged(int index);
		void on_comboBox_axey_0_currentIndexChanged(int index);

		void on_comboBox_enter_currentIndexChanged(int index);
		void on_comboBox_exit_currentIndexChanged(int index);
		void on_comboBox_open_currentIndexChanged(int index);
		void on_comboBox_close_currentIndexChanged(int index);
		void on_comboBox_shock_currentIndexChanged(int index);


		void on_comboBox_in_currentIndexChanged(int index);

		void on_comboBox_out_currentIndexChanged(int index);

	private:
		Ui::zoneEditor *ui;
		eventZone& evz;
};

#endif // ZONEEDITOR_H
