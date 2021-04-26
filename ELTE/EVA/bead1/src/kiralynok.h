#ifndef KIRALYNOK_H
#define KIRALYNOK_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>

class Kiralynok : public QWidget
{
    Q_OBJECT

public:
    Kiralynok(QWidget *parent = 0);
private slots:
    void buttonClicked();
    void newGameButtonClicked();

private:
    void newGame();
    void stepGame(int x, int y);
    void disableButton(int x, int y);
    void enableButton(int x, int y);
    void generateTable();
    void checkGame();

    int stepCount;
    int size;
    int hatra;
    QGridLayout* tableLayout;
    QVBoxLayout* mainLayout;
    QPushButton* newGameButton;
    QVector<QVector<QPushButton*> > buttonTable;
    QLabel *_label; // címke
    QSpinBox *_spinBox; // számbeállító
    QVector<QPushButton*> _buttonGrid;
    int** gameTable;
};

#endif // KIRALYNOK_H
