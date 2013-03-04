#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDebug>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT
		
	public:
		MainWindow(QWidget *parent = 0);
		~MainWindow();
		void init();
//		void closeEvent(QCloseEvent* ev);
		
	public slots:
		void refreshImage();

	private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
