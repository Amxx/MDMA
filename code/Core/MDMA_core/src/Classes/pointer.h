#ifndef POINTER_H
#define POINTER_H

#include <QPoint>

enum vect
{
	POS = 0,
	SPE = 1,
	ACC = 2
};
enum timing
{
	CURRENT = 0,
	PREVIOU = 1
};



class Pointer
{
	public:
		Pointer();
		Pointer(QPoint ps, bool st, int id);

		void update(QPoint ps, bool st);

		int id;
		QPoint vects[3][2];
		bool open[2];
};

#endif // POINTER_H
