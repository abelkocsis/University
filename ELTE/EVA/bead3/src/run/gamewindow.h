#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtGui/QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QHBoxLayout>
#include "gamemanager.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

private slots:
    void startNewGame(); // új játék
    void buttonClicked(); // ha új játék gombra kattintottunk
    void gameManager_ImageChanged(QPixmap image); // megváltozott egy kép
    void gameManager_GameOver(bool won, int kosarak); // vége a játéknak

private:
    GameManager* _gameManager; // játékmenedzser
    // felületi vezérlők:
    QPushButton* _smallGameButton;
    QPushButton* _middleGameButton;
    QPushButton* _largeGameButton;
    QPushButton* _pauseButton;
    QLabel* _messageLabel;
    QLabel* _mainImageLabel;
    QVector<QVector<QPushButton*>> _imageButtons;
    QHBoxLayout* _imageLayout;
};

#endif // GAMEWINDOW_H
