#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QWidget>
#include "tictactoemodel.h"
#include "loadgamewidget.h"
#include "savegamewidget.h"

class TicTacToeWidget : public QWidget // a nézet típusa
{
    Q_OBJECT

public:
    TicTacToeWidget(QWidget *parent = 0);
    ~TicTacToeWidget();

protected:
    void paintEvent(QPaintEvent *);    
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void model_gameWon(TicTacToeModel::Player player); // eseménykezelők a modell eseményeire
    void model_gameOver();
    void model_fieldChanged(int, int, TicTacToeModel::Player);
    void loadGame();
    void saveGame();

private:
    QVector<QLineF> _tableGraphics; // tábla grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> _playerXGraphics; // kereszt grafikája
    QRectF _playerOGraphics; // kör grafikája

    TicTacToeModel _model; // a játékot megvalósító modell
    SaveGameWidget* _saveGameWidget; // a mentést biztosító ablak
    LoadGameWidget* _loadGameWidget; // a betöltést biztostó ablak
};

#endif // TICTACTOEWIDGET_H
