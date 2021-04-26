#include "tictactoemodel.h"

TicTacToeModel::TicTacToeModel()
{
    _gameTable = new Player*[3];
    for (int i = 0; i < 3; ++i)
    {
        _gameTable[i] = new Player[3];
    }
}

TicTacToeModel::~TicTacToeModel()
{
    delete[] _gameTable;
}

void TicTacToeModel::newGame()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            _gameTable[i][j] = NoPlayer; // a játékosok pozícióit töröljük
        }

    _stepNumber = 0;
    _currentPlayer = PlayerX; // először az X lép
}

void TicTacToeModel::stepGame(int x, int y)
{
    if (_stepNumber >= 9) // ellenőrizzük a lépésszámot
        return;
    if (x < 0 || x > 2 || y < 0 || y > 2) // ellenőrizzük a tartomány
        return;
    if (_gameTable[x][y] != 0) // ellenőrizzük a mezőt
        return;

    _gameTable[x][y] = _currentPlayer; // pozíció rögzítése
    fieldChanged(x, y, _currentPlayer); // jelezzük egy eseménykiváltással, hogy változott a mező

    _stepNumber++;
    _currentPlayer = (Player)(_currentPlayer % 2 + 1);
    // egészként kezelhető az érték, de konvertálnunk kell

    checkGame();
}

bool TicTacToeModel::loadGame(int gameIndex)
{
    QVector<int> saveGameData;

    if (!_dataAccess.loadGame(gameIndex, saveGameData)) // az adatelérés végzi a tevékenységeket
        return false;

    // feldolgozttuk a kapott vektort
    _stepNumber = saveGameData[0];
    _currentPlayer = (Player)saveGameData[1];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            _gameTable[i][j] = (Player)saveGameData[2 + i * 3 + j];
        }

    return true;
}

bool TicTacToeModel::saveGame(int gameIndex)
{
    QVector<int> saveGameData;

    // összerakjuk a megfelelő tartalmat
    saveGameData.push_back(_stepNumber);
    saveGameData.push_back((int)_currentPlayer);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            saveGameData.push_back((int)_gameTable[i][j]);
        }

    return _dataAccess.saveGame(gameIndex, saveGameData); // az adatelérés végzi a tevékenységeket
}

QVector<QString> TicTacToeModel::saveGameList() const
{
    return _dataAccess.saveGameList(); // az adatelérés végzi a tevékenységeket
}

TicTacToeModel::Player TicTacToeModel::getField(int x, int y) const
{
    if (x < 0 || x > 2 || y < 0 || y > 2) // ellenőrizzük a tartomány
        return NoPlayer; // már a felsorolt értéket adjuk vissza

    return _gameTable[x][y];
}


void TicTacToeModel::checkGame()
{
    Player won = NoPlayer;

    for(int i = 0; i < 3; ++i) // ellenőrzések végrehajtása
    {
        if (_gameTable[i][0] != 0 && _gameTable[i][0] == _gameTable[i][1] && _gameTable[i][1] == _gameTable[i][2])
            won = _gameTable[i][0];
    }
    for(int i = 0; i < 3; ++i)
    {
        if (_gameTable[0][i] != 0 && _gameTable[0][i] == _gameTable[1][i] && _gameTable[1][i] == _gameTable[2][i])
            won = _gameTable[0][i];
    }
    if (_gameTable[0][0] != 0 && _gameTable[0][0] == _gameTable[1][1] && _gameTable[1][1] == _gameTable[2][2])
        won = _gameTable[0][0];
    if (_gameTable[0][2] != 0 && _gameTable[0][2] == _gameTable[1][1] && _gameTable[1][1] == _gameTable[2][0])
        won = _gameTable[0][2];

    if (won != NoPlayer) // ha valaki győzött
    {
        gameWon(won); // esemény kiváltása
    }
    else if (_stepNumber == 9) // döntetlen játék
    {
        gameOver(); // esemény kiváltása
    }
}
