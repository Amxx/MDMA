#ifndef HANDOPENWINDOW_H
#define HANDOPENWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>

#include "../objects/configuration.h"

namespace Ui {
	class HandOpenWindow;
}

class HandOpenWindow : public QDialog
{
		Q_OBJECT
		
	public:
		HandOpenWindow(QWidget *parent = 0);
		~HandOpenWindow();
		void closeEvent();
		
	private slots:
		void on_pushButton_next_clicked();
		void on_pushButton_cancel_clicked();
		void on_pushButton_clicked();
		void set_number();

	private:
		QTimer timer;
		Ui::HandOpenWindow *ui;
};

#endif // MASKWINDOW_H
