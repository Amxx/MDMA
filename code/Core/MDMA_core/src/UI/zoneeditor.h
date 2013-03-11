#ifndef ZONEEDITOR_H
#define ZONEEDITOR_H

#include <QDialog>
#include <QPoint>

#include "../Utils/define.h"
#include "../Classes/zone.h"

namespace Ui {
	class ZoneEditor;
}

class ZoneEditor : public QDialog
{
		Q_OBJECT
		
	public:
		explicit ZoneEditor(Zone& zn, QWidget* parent = 0);
		~ZoneEditor();
		
	protected:
		void init();

	private slots:
		void on_pushButton_apply_clicked();
		void on_pushButton_delete_clicked();
		void on_pushButton_cancel_clicked();

		void on_tabWidget_type_currentChanged(int index);
		void on_lineEdit_name_textChanged(const QString &arg1);

		void on_comboBox_axex_0_currentIndexChanged(int index);
		void on_spinBox_axex_1_valueChanged(int arg1);
		void on_spinBox_axex_2_valueChanged(int arg1);
		void on_spinBox_axex_3_valueChanged(int arg1);
		void on_radioButton_variable_1_1_toggled(bool checked);

		void on_comboBox_axey_0_currentIndexChanged(int index);
		void on_spinBox_axey_1_valueChanged(int arg1);
		void on_spinBox_axey_2_valueChanged(int arg1);
		void on_spinBox_axey_3_valueChanged(int arg1);
		void on_radioButton_variable_2_1_toggled(bool checked);

		void on_comboBox_enter_currentIndexChanged(int index);
		void on_comboBox_exit_currentIndexChanged(int index);
		void on_comboBox_open_currentIndexChanged(int index);
		void on_comboBox_close_currentIndexChanged(int index);
		void on_comboBox_shock_currentIndexChanged(int index);

		void on_comboBox_in_currentIndexChanged(int index);
		void on_comboBox_out_currentIndexChanged(int index);
		void on_noteHelp_clicked();

	private:
		Ui::ZoneEditor *ui;
		Zone& _zn;
};

int EditZone(Zone& zn, QWidget* parent = 0);

#endif // ZONEEDITOR_H
