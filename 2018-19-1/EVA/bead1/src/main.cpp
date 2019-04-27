#include <QApplication>
#include "kiralynok.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Kiralynok w;
    w.show();

    return a.exec();
}
