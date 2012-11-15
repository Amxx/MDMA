#ifndef NOTENUMBERWINDOW_H
#define NOTENUMBERWINDOW_H

#include <QDialog>

namespace Ui {
	class NoteNumberWindow;
}

class NoteNumberWindow : public QDialog
{
		Q_OBJECT
		
	public:
		explicit NoteNumberWindow(QWidget *parent = 0);
		~NoteNumberWindow();
		
	private slots:
		void on_note_currentIndexChanged();
		void on_octave_currentIndexChanged();

	private:
		void update();

		Ui::NoteNumberWindow *ui;
};

#endif // NOTENUMBERWINDOW_H
