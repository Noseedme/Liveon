
#include "gameWidget.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    w.show();
    w.move(160,30);
    return a.exec();
}
