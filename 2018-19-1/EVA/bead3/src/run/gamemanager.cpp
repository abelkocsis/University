#include "gamemanager.h"


GameManager::GameManager()
{
}

GameManager::~GameManager()
{

}

void GameManager::newGame(int s)
{

    int _number = _size = s;

    table.clear();

    table.resize(_number);

    for (int i = 0; i < _number; i++) // a számokat sorban legeneráljuk
    {
        table[i].resize(_number);
        for (int j = 0; j < _number; j++){
            table[i][j] = 0;
        }
    }

    for (int i = 0; i < _number; i ++){ //legenerálja a kavicsokat
        int x, y;
        x = qrand() % _number;
        y = qrand() % _number;
        while (table[x][y] != 0){
            x = qrand() % _number;
            y = qrand() % _number;
        }
        table[x][y] = 1;

        x = qrand() % _number;
        y = qrand() % _number;
        while (table[x][y] != 0){
            x = qrand() % _number;
            y = qrand() % _number;
        }
        table[x][y] = -1;
    }
    _images.clear();
    for (int i = 0; i < 5; i++)
    {
        _images.append(QPixmap(":/images/" + QString::number(i) + ".png")); // beállítjuk az elérési útvonalukat
    }


    chosen.x = -1;
    _actualPlayer = 1;
    _stepcount = 0;
}

void GameManager::buttonClicked(int x, int y){
    if (chosen.x == -1){
        if (_actualPlayer == table[x][y]){
            chosen.x = x;
            chosen.y = y;
        }
        else{
            chosen.x = -1;
        }
    }
    else if (_isValidStep(x, y)){
        stepGame(x, y);
        _checkGame();
        _actualPlayer *= -1;
        chosen.x = -1;
    }
    else{
        chosen.x = -1;
    }

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

void GameManager::stepGame(int x, int y)
{
    _stepcount++;
    int atm, atm2;
    if (y == chosen.y){
        int i = x;
        atm = table[chosen.x][y];
        table[chosen.x][y] = 0;
        while (i < _size && i >= 0){
            if (atm  == 0)
                break;
            atm2 = table[i][y];
            table[i][y] = atm;
            atm = atm2;
            if (x - chosen.x == -1)
                --i;
            else
                ++i;
        }
    }
    else if (x == chosen.x){
        int j = y;
        atm = table[x][chosen.y];
        table[x][chosen.y] = 0;
        while (j < _size && j >= 0){
            if (atm  == 0)
                break;
            atm2 = table[x][j];
            table[x][j] = atm;
            atm = atm2;
            if (y - chosen.y == -1)
                --j;
            else
                ++j;
        }
    }


    imagesChanged();
    _checkGame();
}

bool GameManager::_isValidStep(int x, int y){
    return ((chosen.x - x == 1 || chosen.x - x == -1) && chosen.y == y) ||
            ((chosen.y - y == 1 || chosen.y - y == -1) && chosen.x == x);
}

void GameManager::_checkGame(){
    int fekete = 0, feher = 0;
    for (int i = 0; i < table.size(); i++){
        for (int j = 0; j < table.size(); j++){
            if (table[i][j] == 1)
                fekete++;
            else if (table[i][j] == -1)
                feher++;
        }
    }
    if (feher == 0){
        emit gameOver(1);
        newGame(table.size());

    }
    else if (fekete == 0){
        emit gameOver(2);
        newGame(table.size());

    }
    else if (_stepcount == 10*table.size()){
        if (fekete > feher){
            emit gameOver(1);
            newGame(table.size());

        }
        else if (feher > fekete){
            emit gameOver(2);
            newGame(table.size());

        }
        else{
            emit gameOver(3);
            newGame(table.size());
        }
    }

    /*for (int i = MaciLaci[0]-1; i < MaciLaci[0]+2; i++ ){
        for (int j = MaciLaci[1]-1; j < MaciLaci[1]+2; j++ ){
            if (i >= 0 && j >= 0 && i < table.size() && j < table.size()){
                if (table[i][j] < 0){
                    _timer->stop();
                    messageChanged(trUtf8("Játék vége! Kezdhetsz újat."));
                    emit gameOver(false, _megszerzettkosarak, _actualTime);
                }

            }
        }
    }
    if (_megszerzettkosarak == _size){
        _timer->stop();
        messageChanged(trUtf8("Játék vége! Kezdhetsz újat."));
        emit gameOver(true, _megszerzettkosarak, _actualTime);
    }*/


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


}

bool GameManager::loadGame(int gameIndex)
{
    QVector<int> saveGameData;

    if (!_dataAccess.loadGame(gameIndex, saveGameData)) // az adatelérés végzi a tevékenységeket
        return false;

    // feldolgozttuk a kapott vektort
    _size = saveGameData[0];
    newGame(_size);
    _stepcount = (int)saveGameData[1];
    if (_stepcount % 2 == 0)
        _actualPlayer = 1;
    else
        _actualPlayer = -1;
    for (int i = 0; i < _size; ++i)
        for (int j = 0; j < _size; ++j)
        {
            table[i][j] = (int)saveGameData[2 + i * _size + j];
        }
    imagesChanged();
    return true;
}

bool GameManager::saveGame(int gameIndex)
{
    QVector<int> saveGameData;

    // összerakjuk a megfelelő tartalmat
    saveGameData.push_back(_size);
    saveGameData.push_back(_stepcount);
    for (int i = 0; i < _size; ++i)
        for (int j = 0; j < _size; ++j)
        {
            saveGameData.push_back((int)table[i][j]);
        }

    return _dataAccess.saveGame(gameIndex, saveGameData); // az adatelérés végzi a tevékenységeket
}

QVector<QString> GameManager::saveGameList() const
{
    return _dataAccess.saveGameList(); // az adatelérés végzi a tevékenységeket
}

int GameManager::currentPlayer(){
    return _actualPlayer;
}
