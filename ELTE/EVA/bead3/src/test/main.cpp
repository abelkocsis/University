#include <QApplication>
#include "tictactoewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TicTacToeWidget widget;
    widget.show();

    return a.exec();
}
