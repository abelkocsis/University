#include "gamewindow2.h"
#include <QMessageBox>
#include <QApplication>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(600,600);
    setWindowTitle(trUtf8("Maci Laci Menekül"));

    _gameManager = new GameManager(); // játékmenedzser osztály
    // kezeljük az eseményeit:
    connect(_gameManager, SIGNAL(imagesChanged()), this, SLOT(gameManager_ImagesChanged()));
    connect(_gameManager, SIGNAL(gameOver(bool, int, int)), this, SLOT(gameManager_GameOver(bool,int,int)));
    connect(this, SIGNAL(keyPressEvent(QKeyEvent)), this, SLOT(gameManager_Step()));

    _smallGameButton = new QPushButton(trUtf8("Könnyű játék (4)"));
    connect(_smallGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    _middleGameButton = new QPushButton(trUtf8("Közepes játék (8)"));
    connect(_middleGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    _largeGameButton = new QPushButton(trUtf8("Nehéz játék (16)"));
    connect(_largeGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));

    _pauseButton = new QPushButton(trUtf8("Szünet/folytatás"));
    _pauseButton->setEnabled(false);
    connect(_pauseButton, SIGNAL(clicked()), _gameManager, SLOT(pauseGame()));

    _messageLabel = new QLabel(trUtf8("Játék kezdéséhez válassz nehézséget!"));
    connect(_gameManager, SIGNAL(messageChanged(QString)), _messageLabel, SLOT(setText(QString)));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(_smallGameButton);
    hLayout->addWidget(_middleGameButton);
    hLayout->addWidget(_largeGameButton);
    hLayout->addWidget(_pauseButton);

    _messageLabel2 = new QLabel(trUtf8("Megszerzett kosarak száma: 0"));
    connect(_gameManager, SIGNAL(messageKosarChanged(QString)), _messageLabel2, SLOT(setText(QString)));

    QVBoxLayout *vLayout = new QVBoxLayout();
    _imageLayout = new QGridLayout();



    vLayout->addLayout(hLayout);
    vLayout->addWidget(_messageLabel, 0, Qt::AlignHCenter);
    vLayout->addWidget(_messageLabel2, 0, Qt::AlignHCenter);
    vLayout->addLayout(_imageLayout);
    setLayout(vLayout);
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
        _gameManager->newGame(4); // létrehozzuk a megfelelõ méretû játékot
        _imageButtons.resize(4);
        setFixedSize(600,670);
    }
    else if (QObject::sender() == _middleGameButton)
    {
        _gameManager->newGame(8);
        _imageButtons.resize(8);
        setFixedSize(600,650);
    }
    else
    {
        _gameManager->newGame(16);
        _imageButtons.resize(16);setFixedSize(600,400 + 600 / _imageButtons.size());
        setFixedSize(600,630);

    }


    _pauseButton->setEnabled(true); // már lehet szüneteltetni



    for (int i = 0; i < _imageButtons.size(); i++)
    {
        _imageButtons[i].resize(_imageButtons.size());

        for (int j = 0; j < _imageButtons.size(); j++){
            _imageButtons[i][j] = new QPushButton();
            _imageButtons[i][j]->setFixedSize(600 / _imageButtons.size(), 600 / _imageButtons.size());
            _imageButtons[i][j]->setIconSize(QSize(600 / _imageButtons.size(), 600 / _imageButtons.size()));
            _imageButtons[i][j]->setIcon(QIcon(_gameManager->getImage(i,j)));

            _imageLayout->addWidget(_imageButtons[i][j], i, j);
        }
    }
    this->setFocus();
}
void GameWindow::gameManager_GameOver(bool won, int megszerzettkosar, int time)
{
     _pauseButton->setEnabled(false);
    if (won)
    {
        QMessageBox::information(this, trUtf8("Játék vége"),
                                 trUtf8("Maci Laci nyert, a ") +
                                 QString::number(megszerzettkosar) + trUtf8(" kosarat ") +
                                 QString::number(time) + trUtf8(" másodperc alatt sikerült megszereznie."));
    }
    else
    {
        QMessageBox::information(this, trUtf8("Játék vége, Gyászhír"),
                                 trUtf8("Sajnálattal tudatjuk Önnel, hogy Medve Lászlót életének ") +
                                 QString::number(time) + trUtf8(". másodpercében megölték."));
    }

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
        }
    }
}
void GameWindow::gameManager_Step(int i){
    _gameManager->stepGame(i);
}
void GameWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Down){
        gameManager_Step(1);
    }
    if(event->key() == Qt::Key_Up){
        gameManager_Step(-1);
    }
    if(event->key() == Qt::Key_Left){
        gameManager_Step(-2);
    }
    if(event->key() == Qt::Key_Right){
        gameManager_Step(2);
    }
}
