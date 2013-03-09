#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDebug>


#include "../core.h"
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
		void mouseReleaseEvent(QMouseEvent *e);
		
	public slots:
		void refreshImage();

	private slots:
		void on_actionNew_triggered();
		void on_actionOpen_triggered();
		void on_actionSave_triggered();
		void on_actionSave_as_triggered();
		void on_actionAbout_MDMA_triggered();

	private:
		Ui::MainWindow *ui;
		ZoneDrager* zd;
};

#endif // MAINWINDOW_H
