#include "agenda.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    agenda w;
    w.show();
    return a.exec();
}
