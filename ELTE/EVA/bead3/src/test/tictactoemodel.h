#ifndef TICTACTOEMODEL_H
#define TICTACTOEMODEL_H

#include <QObject>
#include <QVector>
#include <QString>
#include "tictactoedataaccess.h"

class TicTacToeModel : public QObject // a modell típusa
{
    Q_OBJECT
public:
    enum Player { NoPlayer, PlayerX, PlayerO }; // játékos felsorolási típusa

    TicTacToeModel();
    virtual ~TicTacToeModel();
    void newGame(); // új játék kezdése
    void stepGame(int x, int y); // játék léptetése
    bool loadGame(int gameIndex); // játék betöltése
    bool saveGame(int gameIndex); // játék mentése

    QVector<QString> saveGameList() const; // mentett játékok lekérdezése
    int stepNumber() const { return _stepNumber; } // lépések számának lekérdezése
    Player currentPlayer() const { return _currentPlayer; } // aktuális játékos
    Player getField(int x, int y) const; // játékmező lekérdezése


signals:
    void gameWon(TicTacToeModel::Player player); // játékos győzelmének eseménye
    void gameOver(); // döntetlen játék eseménye
    void fieldChanged(int x, int y, TicTacToeModel::Player player); // mező változásának eseménye

private: 
    void checkGame(); // játék ellenőrzése

    int _stepNumber; // lépések száma
    Player _currentPlayer; // játékos száma
    Player** _gameTable; // játéktábla

    TicTacToeDataAccess _dataAccess; // adatelérés
};

#endif // TICTACTOEMODEL_H
