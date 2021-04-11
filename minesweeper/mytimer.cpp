#include "mytimer.h"

MyTimer::MyTimer(QObject* parent):QTimer(parent)
{
    ct=1;
    start(1000);
}


