#ifndef MASKWINDOW_H
#define MASKWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>

#include "../objects/configuration.h"

namespace Ui {
	class MaskWindow;
}

class MaskWindow : public QDialog
{
		Q_OBJECT
		
	public:
		MaskWindow(Configuration& _config, QWidget *parent = 0);
		~MaskWindow();
		void closeEvent();
		
	private slots:
		void on_pushButton_next_clicked();
		void on_pushButton_cancel_clicked();
		void on_pushButton_clicked();
		void set_number();

	private:
		QTimer timer;
		Configuration& config;
		Ui::MaskWindow *ui;
};

#endif // MASKWINDOW_H
