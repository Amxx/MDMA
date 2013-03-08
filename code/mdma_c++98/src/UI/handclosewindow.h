#ifndef HANDCLOSEWINDOW_H
#define HANDCLOSEWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>

#include "../objects/configuration.h"

namespace Ui {
	class HandCloseWindow;
}

class HandCloseWindow : public QDialog
{
		Q_OBJECT
		
	public:
        HandCloseWindow(cv::Mat&, QWidget *parent = 0);
		~HandCloseWindow();
		void closeEvent();
		
	private slots:
		void on_pushButton_next_clicked();
		void on_pushButton_cancel_clicked();
		void on_pushButton_clicked();
		void set_number();

	private:
		QTimer timer;
		Ui::HandCloseWindow *ui;
        cv::Mat& mat;
};

#endif // MASKWINDOW_H
