#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDebug>


#include "../Widgets/zonedrager.h"

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
		void mousePressEvent(QMouseEvent *e);
		void mouseMoveEvent(QMouseEvent *e);
		
	public slots:
		void refreshImage();

	private:
		Ui::MainWindow *ui;



		ZoneDrager* zd;
};

#endif // MAINWINDOW_H
