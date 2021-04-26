#include "gamemanager.h"

#include <QTime>

GameManager::GameManager()
{
    _timer = new QTimer();
    _timer->setInterval(1000);

    qsrand(QTime::currentTime().msec());

    connect(_timer, SIGNAL(timeout()), this, SLOT(timer()));
}

GameManager::~GameManager()
{
    _timer->stop();
    delete _timer;
}

void GameManager::newGame(int s)
{


    if (_timer->isActive())
        _timer->stop(); // időzítő leáll

    _actualTime = 0;
    int _number = _size = s;
    _megszerzettkosarak = 0;
    table.clear();

    table.resize(_number);

    for (int i = 0; i < _number; i++) // a számokat sorban legeneráljuk
    {
        table[i].resize(_number);
        for (int j = 0; j < _number; j++){
            table[i][j] = 0;
        }
    }
    table[0][0] = 69;
    erdeszet.clear();
    Vador atm;
    for (int i = 0; i < _number/2 - 1 ; i ++){ //legenerálja a Vadőröket
        atm.irany = (qrand() % 2 ) + 1;
        if (qrand() % 2 == 0)
            atm.irany *= -1;
        atm.pos.x = qrand() % _number;
        atm.pos.y = qrand() % _number;
        while (table[atm.pos.x][atm.pos.y] != 0 || (atm.pos.x < 2 && atm.pos.y < 2)){
            atm.pos.x = qrand() % _number;
            atm.pos.y = qrand() % _number;
        }
        erdeszet.push_back(atm);
        table[atm.pos.x][atm.pos.y] = -5;
    }
    int x, y;
    for (int i = 0; i < _number/2 - 1; i ++){ //legenerálja az akadályokat
        x = qrand() % _number;
        y = qrand() % _number;
        while (table[x][y] != 0){
            x = qrand() % _number;
            y = qrand() % _number;
        }
        table[x][y] = 1;
    }
    _images.clear();
    for (int i = 0; i < 5; i++)
    {
        _images.append(QPixmap(":/images/" + QString::number(i) + ".png")); // beállítjuk az elérési útvonalukat
    }

    for (int i = 0; i < _number; i ++){ //legenerálja a kosarakat
        x = qrand() % _number;
        y = qrand() % _number;
        while (table[x][y] != 0){
            x = qrand() % _number;
            y = qrand() % _number;
        }
        table[x][y] = 2;
    }

    MaciLaci[0] = 0;
    MaciLaci[1] = 0;
    messageKosarChanged(trUtf8("Megszerzett kosarak száma: ") + QString::number(_megszerzettkosarak));
    _timer->start(); // időzítő indul
}

void GameManager::pauseGame()
{


    if (_timer->isActive()) // ha megy az időzítő
    {
        messageChanged(trUtf8("Pihi van."));
        _timer->stop(); // leállítjuk
    }
    else
        _timer->start(); // különben elindít

}

void GameManager::stepGame(int nr)
{
   if (_timer->isActive() && nr >= -2 && nr <= 2)
   {
        if (_isValidStep(MaciLaci[0], MaciLaci[1], nr)){
            table[MaciLaci[0]][MaciLaci[1]] = 0;
            switch (nr){
                case 1:
                    MaciLaci[0]++;
                break;
                case -1:
                    MaciLaci[0]--;
                break;
                case 2:
                    MaciLaci[1]++;
                break;
                case -2:
                    MaciLaci[1]--;
                break;
            default:
                break;
            }
            if (table[MaciLaci[0]][MaciLaci[1]] == 2){
                _megszerzettkosarak++;
                messageKosarChanged(trUtf8("Megszerzett kosarak száma: ") + QString::number(_megszerzettkosarak));
            }
            table[MaciLaci[0]][MaciLaci[1]] = 69;

        }
   }
   imagesChanged();
   _checkGame();
}

bool GameManager::_isValidStep(int x, int y, int i){
    switch (i){
        case 1:
            return (x < table.size()-1) && table[x+1][y] != 1;
        break;
        case -1:
            return x > 0 && table[x-1][y] != 1;
        break;
        case -2:
            return y > 0 && table[x][y-1] != 1;
        break;
        case 2:
            return y < table.size()-1 && table[x][y+1] != 1;
        break;
    default:
        break;
}
}

void GameManager::_checkGame(){
    bool end = false;
    for (int i = MaciLaci[0]-1; i < MaciLaci[0]+2; i++ ){
        for (int j = MaciLaci[1]-1; j < MaciLaci[1]+2; j++ ){
            if (i >= 0 && j >= 0 && i < table.size() && j < table.size()){
                if (table[i][j] < 0){
                    _timer->stop();
                    messageChanged(trUtf8("Játék vége! Kezdhetsz újat."));
                    emit gameOver(false, _megszerzettkosarak, _actualTime);
                    end = true;
                }

            }
        }
    }
    if (_megszerzettkosarak == _size && !end){
        _timer->stop();
        messageChanged(trUtf8("Játék vége! Kezdhetsz újat."));
        emit gameOver(true, _megszerzettkosarak, _actualTime);
    }


}

const QPixmap& GameManager::getImage (int i, int j) const
{
    if (table[i][j] == 0)
        return _images[0];
    else if (table[i][j] == 1)
        return _images[1];
    else if (table[i][j] < 0)
        return _images[3];
    else if (table[i][j] == 2)
        return _images[2];
    else
        return _images[4];
}

void GameManager::timer()
{

        _actualTime++;
        messageChanged(trUtf8("Idő: ") + QString::number(_actualTime) + trUtf8(" másodperc."));

        if (_actualTime % 2 == 0){
            vadorStep();
        }


}

void GameManager::vadorStep(){
    for (int i = 0; i < erdeszet.size(); i++){
        Vador atm = erdeszet[i];
        table[atm.pos.x][atm.pos.y] += 5;
        if (_isValidStep(atm.pos.x, atm.pos.y, atm.irany)){
            switch (atm.irany){
                case 1:
                    atm.pos.x++;
                break;
                case -1:
                    atm.pos.x--;
                break;
                case -2:
                    atm.pos.y--;
                break;
                case 2:
                    atm.pos.y++;
                break;
            default:
                break;
        }
        }
        else if (_isValidStep(atm.pos.x, atm.pos.y, -atm.irany)){
            atm.irany *= -1;
            switch (atm.irany){
                case 1:
                    atm.pos.x++;
                break;
                case -1:
                    atm.pos.x--;
                break;
                case -2:
                    atm.pos.y--;
                break;
                case 2:
                    atm.pos.y++;
                break;
            default:
                break;
        }


    }
    erdeszet[i] = atm;
    table[atm.pos.x][atm.pos.y] -= 5;
}
     imagesChanged();
     _checkGame();
}

