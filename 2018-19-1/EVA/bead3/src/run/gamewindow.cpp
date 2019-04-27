#include "gamewindow.h"
#include <QMessageBox>
#include <QApplication>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(600,400);
    setWindowTitle(trUtf8("Memóriajáték"));

    _gameManager = new GameManager(); // játékmenedzser osztály, 30 másodperces játékkal
    // kezeljük az eseményeit:
    //connect(_gameManager, SIGNAL(imageChanged(QPixmap)), this, SLOT(gameManager_ImageChanged(QPixmap)));
    connect(_gameManager, SIGNAL(gameOver(int, int)), this, SLOT(gameManager_GameOver(int,int)));

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

    _mainImageLabel = new QLabel("");
    _mainImageLabel->setFixedSize(300, 300);
    _mainImageLabel->setFrameStyle(QFrame::Raised);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(_smallGameButton);
    hLayout->addWidget(_middleGameButton);
    hLayout->addWidget(_largeGameButton);
    hLayout->addWidget(_pauseButton);
    QVBoxLayout *vLayout = new QVBoxLayout();
    _imageLayout = new QHBoxLayout();
    vLayout->addLayout(hLayout);
    vLayout->addWidget(_messageLabel, 0, Qt::AlignHCenter);
    vLayout->addWidget(_mainImageLabel, 0, Qt::AlignHCenter);
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
        for (int j = 0; j <_imageButtons.size(); j++ ){
            _imageLayout->removeWidget(_imageButtons[i][j]); // a régi gombokat töröljük
            delete _imageButtons[i][j];
        }

    }

    if (QObject::sender() == _smallGameButton) // attól függ, melyik gombra kattintottunk
    {
        _gameManager->newGame(4); // létrehozzuk a megfelelõ méretû játékot
        _imageButtons.resize(4);
    }
    else if (QObject::sender() == _middleGameButton)
    {
        _gameManager->newGame(8);
        _imageButtons.resize(8);
    }
    else
    {
        _gameManager->newGame(16);
        _imageButtons.resize(16);
    }
    _pauseButton->setEnabled(true); // már lehet szüneteltetni
    _mainImageLabel->setPixmap(QPixmap());
    setFixedSize(600,400 + 600 / _imageButtons.size());

    for (int i = 0; i < _imageButtons.size(); i++)
    {
        for (int j = 0; j < _imageButtons.size(); j++){
            _imageButtons[i][j] = new QPushButton();
            _imageButtons[i][j]->setFixedSize(600 / _imageButtons.size(), 600 / _imageButtons.size());
            _imageButtons[i][j]->setIconSize(QSize(600 / _imageButtons.size(),600 / _imageButtons.size()));
            //Ezzel rakunk rá valamit.
            _imageButtons[i][j]->setIcon(QIcon(_gameManager->getImage(i, j)));
            // kezdetben felhelyezzük a képeket
            //connect(_imageButtons[i], SIGNAL(clicked()), this, SLOT(buttonClicked()));
            _imageLayout->addWidget(_imageButtons[i][j]);
        }

    }
}

//?!!!
void GameWindow::buttonClicked()
{
    if (!_gameManager->canPlay()) // ha nam kattinthat nem csinálunk semmit
        return;

    int nr = _imageLayout->indexOf(qobject_cast<QPushButton*>(sender())); // lekérjük a küldő sorszámát

    //_imageButtons[nr]->setIcon(_gameManager->getImage(nr));
    _gameManager->stepGame(nr); // léptetjük a játékot
       // a megadott gombon váltjuk a képet
}

//Ez még kellhet, ez szórakozik a képekkel.

void GameWindow::gameManager_ImageChanged(QPixmap image)
{
    for (int i = 0; i < _imageButtons.size(); i++){
        for (int j = 0; j < _imageButtons.size(); j++){
             _imageButtons[i][j]->setIcon(QIcon()); // letakarítjuk a képeket
        }
    }


    //_mainImageLabel->setPixmap(image.scaled(_mainImageLabel->width(), _mainImageLabel->height()));
    // beállíjuk a központi képet
}

void GameWindow::gameManager_GameOver(bool won, int kosarak)
{
    if (won)
    {
        QMessageBox::information(this, trUtf8("Játék vége, Maci Laci nyert!"),
                                 trUtf8("Összesen ") +
                                 QString::number(kosarak) + trUtf8(" összegyűjtött kosár."));
    }
    else
    {
        QMessageBox::information(this, trUtf8("Játék vége"),
                                 trUtf8("Maci Lacit véresen megölték."));
    }
}

