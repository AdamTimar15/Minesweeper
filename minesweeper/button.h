#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QObject>
#include <QMouseEvent>
#include <QPixmap>
#include <QIcon>


class Button: public QPushButton
{
    Q_OBJECT
public:
    Button(int status,int row,int column,QPushButton* parent=nullptr);
    int status;
    int number;
    int row;
    int column;
    QIcon bombIcon;
    QIcon flagIcon;
    QPixmap qp1;
    QPixmap qp2;
    bool flag=false;
    void mousePressEvent(QMouseEvent* ev);
    void setTextColor(const QString& text);

signals:
    void flagPlus();
    void flagMinus();
    void bombFound();
    void zeros();
    void pressed();

};

#endif // BUTTON_H
