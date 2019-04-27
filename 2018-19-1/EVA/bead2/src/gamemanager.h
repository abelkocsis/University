#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QTimer>
#include <QIcon>
#include <QPixmap>

struct Position {
    int x;
    int y;
};

struct Vador {
    Position pos;
    int irany;
};

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager();
    ~GameManager();
    bool canPlay() const { return _timer->isActive(); } // lehet-e lépni a játékban

public slots:
    void newGame(int s); // új játék
    void pauseGame(); // játék szüneteltetése
    void stepGame(int nr); // lépés a játékban
    const QPixmap& getImage(int i, int j) const;



private slots:
    void timer(); // időzítő eseménykezelője

signals:
    void messageChanged(QString message); // üzenetváltás eseménye
    void imagesChanged(); // képváltás eseménye
    void gameOver(bool won, int kosarak, int time); // játék vége eseménye
    void messageKosarChanged(QString message);

private:
    QVector<QVector<int>> table;
    int _size;
    int _actualTime; // kezdeti idő (az előnézethez)
    int _megszerzettkosarak;
    void vadorStep();
    QVector<Vador> erdeszet;
    int MaciLaci[2];
    bool _isValidStep(int x, int y, int i);
    QTimer* _timer; // idõzítő
    void _checkGame();
    QVector<QPixmap> _images;
};

#endif // GAMEMANAGER_H
