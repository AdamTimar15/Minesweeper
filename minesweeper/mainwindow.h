#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "button.h"
#include "mytimer.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <QGridLayout>
#include <QLCDNumber>
#include <QElapsedTimer>
#include <QList>
#include <QMessageBox>
#include <QThread>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int mRows,int bombs,QWidget *parent = nullptr);
    ~MainWindow();
    struct Matrix{
        int number;
        int status;
    };
    int mRows;
    int bombs;
    int flags;
    Matrix** matrix;
    QIcon icon;
    QLCDNumber* led1;
    QLCDNumber* led2;
    QPushButton* newGame;
    MyTimer* timer;
    QList<Button*> buttons;
    void futas();
    void generateBombs();
    void setNumbers();
    int neighboursSum(int i,int j);
    void printMatrix();
    void showBobms();
    void restart();
    Button* getButton(int i,int j);
    void zeroFields(int i,int j);
    void showNeighbours(int i,int j);
    void win();
    void printStatus();
    void updateStatus();
    void setupMap();


public slots:
    void ledPlus();
    void ledMinus();
    void changeLed();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
