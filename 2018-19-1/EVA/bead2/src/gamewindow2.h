#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H

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
    void keyPressEvent(QKeyEvent *event);
    void gameManager_ImagesChanged(); // megváltozott egy kép
    void gameManager_GameOver(bool won, int megszerzettkosar, int time); // vége a játéknak
    void gameManager_Step(int i);
private:
    GameManager* _gameManager; // játékmenedzser
    // felületi vezérlők:
    QPushButton* _smallGameButton;
    QPushButton* _middleGameButton;
    QPushButton* _largeGameButton;
    QPushButton* _pauseButton;
    QLabel* _messageLabel;
    QLabel* _messageLabel2;
    QVector<QVector<QPushButton*>> _imageButtons;
    QGridLayout* _imageLayout;

};

#endif // GAMEWINDOW2_H
