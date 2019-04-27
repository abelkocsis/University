#include "kiralynok.h"
#include <QMessageBox>

Kiralynok::Kiralynok(QWidget *parent)
    : QWidget(parent)
{

    setMinimumSize(600, 600);
    setBaseSize(600,600);
    setWindowTitle(trUtf8("Kiralynők"));

    newGameButton = new QPushButton(trUtf8("Új játék")); // új játék gomb
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));

    _label = new QLabel(trUtf8("Tábla mérete: "));
    _label->setFixedHeight(20);

    _spinBox = new QSpinBox();
    _spinBox->setFixedHeight(20);
    _spinBox->setFixedWidth(80);
    _spinBox->setSingleStep(2);
    _spinBox->setRange(4,8);


    mainLayout = new QVBoxLayout(); // vertikális elhelyezkedés a teljes felületnek
    mainLayout->addWidget(_label);
    mainLayout->addWidget(_spinBox);
    mainLayout->addWidget(newGameButton);


    tableLayout = new QGridLayout(); // rácsos elhelyezkedés a játékmezőnek


    newGame();
    mainLayout->addLayout(tableLayout);
    setLayout(mainLayout);


}




void Kiralynok::buttonClicked(){
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = tableLayout->indexOf(senderButton);

    stepGame(location / size, location % size);
}

void Kiralynok::newGameButtonClicked(){
    newGame();
}

void Kiralynok::newGame(){

    size = _spinBox->value();
    generateTable();
    stepCount = 0;
    hatra = size;
    for (int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            gameTable[i][j] = 0; // a játékosok pozícióit töröljük
            buttonTable[i][j]->setText(""); // a szöveget töröljük
            buttonTable[i][j]->setEnabled(true); // bekapcsoljuk a gombot
            QPalette pal = buttonTable[i][j]->palette();
            pal.setColor(QPalette::Button, QColor(Qt::white));
            buttonTable[i][j]->setAutoFillBackground(true);
            buttonTable[i][j]->setPalette(pal);

        }
    }
}

void Kiralynok::stepGame(int x, int y){
    if (gameTable[x][y] == 0){
        gameTable[x][y] = 1;
        buttonTable[x][y]->setText("");
        QPalette pal = buttonTable[x][y]->palette();
        pal.setColor(QPalette::Button, QColor(Qt::green));
        buttonTable[x][y]->setAutoFillBackground(true);
        buttonTable[x][y]->setPalette(pal);

        for (int i = 0; i < size; ++i){
            if (i != x){
                disableButton(i, y);
            }
        }
        for (int j = 0; j < size; ++j){
            if (j != y){
                disableButton(x, j);
            }
        }
        int i = x - 1;
        int j = y - 1;
        while (i >= 0 && j >= 0){
            disableButton(i, j);
            --i;
            --j;
        }
        i = x-1;
        j = y + 1;
        while (i >= 0 && j < size){
            disableButton(i, j);
            --i;
            ++j;
        }
        i = x+1;
        j = y - 1;
        while (i < size && j >= 0){
            disableButton(i, j);
            ++i;
            --j;
        }

        i = x+1;
        j = y + 1;
        while (i < size && j < size){
            disableButton(i, j);
            ++i;
            ++j;
        }


        hatra--;
    }
    else{
        gameTable[x][y] = 0;
        buttonTable[x][y]->setText("");
        QPalette pal = buttonTable[x][y]->palette();
        pal.setColor(QPalette::Button, QColor(Qt::white));
        buttonTable[x][y]->setAutoFillBackground(true);
        buttonTable[x][y]->setPalette(pal);

        for (int i = 0; i < size; ++i){
            if (i != x){
                enableButton(i, y);
            }
        }
        for (int j = 0; j < size; ++j){
            if (j != y){
                enableButton(x, j);
            }
        }
        int i = x - 1;
        int j = y - 1;
        while (i >= 0 && j >= 0){
            enableButton(i, j);
            --i;
            --j;
        }
        i = x-1;
        j = y + 1;
        while (i >= 0 && j < size){
            enableButton(i, j);
            --i;
            ++j;
        }
        i = x+1;
        j = y - 1;
        while (i < size && j >= 0){
            enableButton(i, j);
            ++i;
            --j;
        }

        i = x+1;
        j = y + 1;
        while (i < size && j < size){
            enableButton(i, j);
            ++i;
            ++j;
        }


        hatra++;
    }



    stepCount++;
    checkGame();

}

void Kiralynok::disableButton(int x, int y){
    gameTable[x][y]--;
    buttonTable[x][y]->setEnabled(false);

    QPalette pal = buttonTable[x][y]->palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    buttonTable[x][y]->setAutoFillBackground(true);
    buttonTable[x][y]->setPalette(pal);
}

void Kiralynok::enableButton(int x, int y){
    gameTable[x][y]++;
    if (gameTable[x][y] == 0){
        QPalette pal = buttonTable[x][y]->palette();
        pal.setColor(QPalette::Button, QColor(Qt::white));
        buttonTable[x][y]->setAutoFillBackground(true);
        buttonTable[x][y]->setPalette(pal);
        buttonTable[x][y]->setText("");
        buttonTable[x][y]->setEnabled(true);
    }

}

void Kiralynok::generateTable(){
    setFixedSize(size*75,size*75);

    foreach(QPushButton* button, _buttonGrid) // korábbi gombok
    {
        tableLayout->removeWidget(button); // levétel az elrendezésről
        delete button; // vezérlő törlése
    }
    _buttonGrid.clear();

    gameTable = new int*[size];
    buttonTable.resize(size);
    for (int i = 0; i < size; ++i)
    {
        gameTable[i] = new int[size];
        buttonTable[i].resize(size);
        for (int j = 0; j < size; ++j)
        {
            buttonTable[i][j]= new QPushButton(this);
            buttonTable[i][j]->setFont(QFont("Times New Roman", 100, QFont::Bold));
            buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            tableLayout->addWidget(buttonTable[i][j], i, j); // gombok felvétele az elhelyezésbe
            _buttonGrid.append(buttonTable[i][j]);
            connect(buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
}

void Kiralynok::checkGame(){
    if (hatra == 0){
        QMessageBox::information(this, trUtf8("Játék vége!"), trUtf8("Megnyerte a játékot %1 lépésből!").arg(stepCount));

        newGame();
    }

}

