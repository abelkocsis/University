#include "savegamewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SaveGameWidget::SaveGameWidget(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Tic-Tac-Toe - Játék mentése");

    _listWidget = new QListWidget();
    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Mégse");

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(_okButton);
    hlayout->addWidget(_cancelButton);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(_listWidget);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void SaveGameWidget::setGameList(QVector<QString> saveGameList)
{
    _listWidget->clear();

    // betöltjük az elemeket a listából
    for (int i = 0; i < 5; i++)
    {
        if (i < saveGameList.size() && !saveGameList[i].isEmpty())
            _listWidget->addItem(saveGameList[i]);
        else
            _listWidget->addItem("üres"); // ami nincs megadva, az üres lesz
    }
}
