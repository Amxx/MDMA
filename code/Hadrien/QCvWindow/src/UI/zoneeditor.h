#ifndef ZONEEDITOR_H
#define ZONEEDITOR_H

#include <QDialog>
#include <QPoint>

#include "../classes/configuration.h"

namespace Ui {
	class zoneEditor;
}

class zoneEditor : public QDialog
{
		Q_OBJECT
		
	public:
		explicit zoneEditor(eventZone* _evz, QWidget* parent = 0);
		~zoneEditor();
		
	protected:
		void init();

	private slots:
		void on_comboBox_axes_currentIndexChanged(int index);

		void on_buttonBox_accepted();

	private:
		Ui::zoneEditor *ui;
		eventZone* evz;
};

#endif // ZONEEDITOR_H
