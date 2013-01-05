#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>

#include "../objects/configuration.h"

namespace Ui {
	class SecondWindow;
}

class SecondWindow : public QDialog, public QPainter
{
		Q_OBJECT
		
	public:
		explicit SecondWindow(QWidget *parent = 0);
		~SecondWindow();
		void closeEvent(QCloseEvent* ev);

		Ui::SecondWindow *ui;
};

#endif // SECONDWINDOW_H
