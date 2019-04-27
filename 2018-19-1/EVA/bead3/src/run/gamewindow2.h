#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H

#include <QtGui/QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QWidget>
#include <QHBoxLayout>
#include "gamemanager.h"
#include "loadgamewidget.h"
#include "savegamewidget.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void startNewGame(); // új játék
    void gameManager_ImagesChanged(); // megváltozott egy kép
    void gameManager_GameOver(int e); // vége a játéknak
    void buttonClicked();
    void loadGame();
    void saveGame();

private:
    GameManager* _gameManager; // játékmenedzser
    // felületi vezérlők:
    QPushButton* _smallGameButton;
    QPushButton* _middleGameButton;
    QPushButton* _largeGameButton;

    QLabel* _messageLabel;
    QLabel* _messageLabel2;
    QVector<QVector<QPushButton*>> _imageButtons;
    QGridLayout* _imageLayout;
    SaveGameWidget* _saveGameWidget; // a mentést biztosító ablak
    LoadGameWidget* _loadGameWidget; // a betöltést biztostó ablak

};

#endif // GAMEWINDOW2_H
