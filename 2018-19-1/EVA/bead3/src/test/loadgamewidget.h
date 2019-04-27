#ifndef LOADGAMEWIDGET_H
#define LOADGAMEWIDGET_H

#include "savegamewidget.h"

class LoadGameWidget : public SaveGameWidget // játék betöltő ablak
{
    Q_OBJECT
public:
    explicit LoadGameWidget(QWidget *parent = 0);

protected slots:
    void okButton_Clicked();
};

#endif // LOADGAMEWIDGET_H
