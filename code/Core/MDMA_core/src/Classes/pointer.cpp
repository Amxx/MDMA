#include "pointer.h"



#include <QDebug>

Pointer::Pointer()
{
}

Pointer::Pointer(QPoint ps, bool st, int id) : id(id)
{
	vects[POS][PREVIOU] = vects[POS][CURRENT] = ps;
	open[PREVIOU] = open[CURRENT] = st;
}


void Pointer::update(QPoint ps, bool st)
{
	qDebug() << "[" << id <<  "]"<< "POSition:" << ps << "- state:" << st;

	vects[POS][PREVIOU] =	vects[POS][CURRENT];
	vects[POS][CURRENT] =	ps;
	vects[SPE][PREVIOU] =	vects[SPE][CURRENT];
	vects[SPE][CURRENT] =	vects[POS][CURRENT] - vects[POS][PREVIOU];
	vects[ACC][PREVIOU] =	vects[ACC][CURRENT];
	vects[ACC][CURRENT] =	vects[SPE][CURRENT] - vects[SPE][PREVIOU];
	open[PREVIOU] =		open[CURRENT];
}

