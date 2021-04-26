#include "gamewindow2.h"
#include <QMessageBox>
#include <QApplication>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{

    //_loadGameWidget = NULL;
    _saveGameWidget = NULL;

    setFixedSize(600,600);
    setWindowTitle(trUtf8("Maci Laci Menekül"));

    _gameManager = new GameManager(); // játékmenedzser osztály
    // kezeljük az eseményeit:
    connect(_gameManager, SIGNAL(imagesChanged()), this, SLOT(gameManager_ImagesChanged()));
    connect(_gameManager, SIGNAL(gameOver(int)), this, SLOT(gameManager_GameOver(int)));


    _smallGameButton = new QPushButton(trUtf8("Könnyű játék (4)"));
    connect(_smallGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    _middleGameButton = new QPushButton(trUtf8("Közepes játék (8)"));
    connect(_middleGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    _largeGameButton = new QPushButton(trUtf8("Nehéz játék (16)"));
    connect(_largeGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));


    _messageLabel = new QLabel(trUtf8("Játék kezdéséhez válassz nehézséget!"));
    connect(_gameManager, SIGNAL(messageChanged(QString)), _messageLabel, SLOT(setText(QString)));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(_smallGameButton);
    hLayout->addWidget(_middleGameButton);
    hLayout->addWidget(_largeGameButton);


    _messageLabel2 = new QLabel(trUtf8("Megszerzett kosarak száma: 0"));
    connect(_gameManager, SIGNAL(messageKosarChanged(QString)), _messageLabel2, SLOT(setText(QString)));

    QVBoxLayout *vLayout = new QVBoxLayout();
    _imageLayout = new QGridLayout();



    vLayout->addLayout(hLayout);
    vLayout->addWidget(_messageLabel, 0, Qt::AlignHCenter);
    vLayout->addWidget(_messageLabel2, 0, Qt::AlignHCenter);
    vLayout->addLayout(_imageLayout);
    setLayout(vLayout);

    _gameManager->newGame(3);
}

GameWindow::~GameWindow()
{
    delete _gameManager;
}

void GameWindow::startNewGame()
{
    for (int i = 0; i < _imageButtons.size(); i++)
    {
         for (int j = 0; j <_imageButtons[i].size(); j++){
            _imageLayout->removeWidget(_imageButtons[i][j]);
            delete _imageButtons[i][j];
        }
    }

    if (QObject::sender() == _smallGameButton) // attól függ, melyik gombra kattintottunk
    {
        _gameManager->newGame(3); // létrehozzuk a megfelelõ méretû játékot
        _imageButtons.resize(3);
        setFixedSize(600,670);
    }
    else if (QObject::sender() == _middleGameButton)
    {
        _gameManager->newGame(4);
        _imageButtons.resize(4);
        setFixedSize(600,650);
    }
    else
    {
        _gameManager->newGame(6);
        _imageButtons.resize(6);setFixedSize(600,400 + 600 / _imageButtons.size());
        setFixedSize(600,630);

    }





    for (int i = 0; i < _imageButtons.size(); i++)
    {
        _imageButtons[i].resize(_imageButtons.size());

        for (int j = 0; j < _imageButtons.size(); j++){
            _imageButtons[i][j] = new QPushButton();
            _imageButtons[i][j]->setFixedSize(600 / _imageButtons.size(), 600 / _imageButtons.size());
            _imageButtons[i][j]->setIconSize(QSize(600 / _imageButtons.size(), 600 / _imageButtons.size()));
            _imageButtons[i][j]->setIcon(QIcon(_gameManager->getImage(i,j)));
            connect(_imageButtons[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));

            _imageLayout->addWidget(_imageButtons[i][j], i, j);
        }
    }
    this->setFocus();
}
void GameWindow::gameManager_GameOver(int e)
{

    if (e == 1)
    {
        QMessageBox::information(this, trUtf8("Játék vége"),
                                 trUtf8("Fekete nyert!"));
    }
    else if ( e == 2)
    {
        QMessageBox::information(this, trUtf8("Játék vége"),
                                 trUtf8("Fehér nyert!"));
    }else{
        QMessageBox::information(this, trUtf8("Játék vége"),
                                 trUtf8("Döntetlen!"));
    }

}
void GameWindow::buttonClicked(){
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = _imageLayout->indexOf(senderButton);
    int x = location / _imageButtons.size();
    int y = location % _imageButtons.size();
    _gameManager->buttonClicked(x, y);
}

void GameWindow::gameManager_ImagesChanged(){
    for (int i = 0; i < _imageButtons.size(); i++)
    {
         for (int j = 0; j <_imageButtons[i].size(); j++){
            _imageLayout->removeWidget(_imageButtons[i][j]);
            delete _imageButtons[i][j];
        }
    }
    for (int i = 0; i < _imageButtons.size(); i++)
    {
        _imageButtons[i].resize(_imageButtons.size());

        for (int j = 0; j < _imageButtons.size(); j++){
            _imageButtons[i][j] = new QPushButton();
            _imageButtons[i][j]->setFixedSize(600 / _imageButtons.size(), 600 / _imageButtons.size());
            _imageButtons[i][j]->setIconSize(QSize(600 / _imageButtons.size(),600 / _imageButtons.size()));
            _imageButtons[i][j]->setIcon(QIcon(_gameManager->getImage(i,j)));
            _imageLayout->addWidget(_imageButtons[i][j], i, j);
            connect(_imageButtons[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_N && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        // lekezeljük a Ctrl+N kombinációt
        _gameManager->newGame(3);
    }

    // játék betöltése
    if (event->key() == Qt::Key_L && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_loadGameWidget == NULL) // ha még egyszer sem nyitották meg az ablakot
        {
            _loadGameWidget = new LoadGameWidget();
            connect(_loadGameWidget, SIGNAL(accepted()), this, SLOT(loadGame()));
        }

        // beállítjuk a listát, és megnyitjuk az ablakot
        _loadGameWidget->setGameList(_gameManager->saveGameList());
        _loadGameWidget->open();
    }

    // játék mentése
    if (event->key() == Qt::Key_S && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_saveGameWidget == NULL) // ha még egyszer sem nyitották meg az ablakot
        {
            _saveGameWidget = new SaveGameWidget();
            connect(_saveGameWidget, SIGNAL(accepted()), this, SLOT(saveGame()));
        }

        // beállítjuk a listát, és megnyitjuk az ablakot
        _saveGameWidget->setGameList(_gameManager->saveGameList());
        _saveGameWidget->open();
    }
}

void GameWindow::saveGame()
{
    // elmentjük a kiválasztott játékot

    if (_gameManager->saveGame(_saveGameWidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, trUtf8("Kitolás"), trUtf8("Játék sikeresen mentve!"));
    }
    else
    {
        QMessageBox::warning(this, trUtf8("Kitolás"), trUtf8("A játék mentése sikertelen!"));
    }
}

void GameWindow::loadGame()
{
    // betöltjük a kiválasztott játékot
    if (_gameManager->loadGame(_loadGameWidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, trUtf8("Kitolás"), trUtf8("Játék betöltve, következik: ") + ((_gameManager->currentPlayer() == 1) ? "fekete" : "fehér") + "!");
    }
    else
    {
        QMessageBox::warning(this, trUtf8("Kitolás"), trUtf8("A játék betöltése sikertelen!"));
    }
}



