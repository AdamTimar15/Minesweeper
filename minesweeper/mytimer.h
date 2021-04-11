#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>

class MyTimer:public QTimer
{
    Q_OBJECT
public:
    MyTimer(QObject* parent=nullptr);
    int ct;


signals:
    void showOnLcd();
};

#endif // MYTIMER_H
