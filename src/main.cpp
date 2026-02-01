#include <QtGui/QApplication>
#include "Hauptfenster.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Hauptfenster fenster;
    fenster.resize(440, 260);
    fenster.show();

    return app.exec();
}
