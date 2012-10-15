#include <QApplication>
#include "mafenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MaFenetre wid;
    wid.show();

    return app.exec();
}
