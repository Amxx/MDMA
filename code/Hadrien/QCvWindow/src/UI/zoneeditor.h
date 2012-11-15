#ifndef ZONEEDITOR_H
#define ZONEEDITOR_H

#include <QDialog>
#include <QPoint>

#include "notenumberwindow.h"
#include "../objects/configuration.h"

namespace Ui {
	class ZoneEditor;
}

class ZoneEditor : public QDialog
{
		Q_OBJECT
		
	public:
		explicit ZoneEditor(EventZone& _evz, QWidget* parent = 0);
		~ZoneEditor();
		
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

		void on_buttonBox_rejected();

		void on_noteHelp_clicked();

	private:
		Ui::ZoneEditor *ui;
		EventZone& evz;
};

#endif // ZONEEDITOR_H
