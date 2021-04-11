#include "button.h"

Button::Button(int status,int row,int column,QPushButton* parent):QPushButton(parent)
{
    this->status=status;
    this->row=row;
    this->column=column;

    setStyleSheet("font-size:14px;background-color:#E0E0E0;");
    setMaximumSize(30,30);

    qp1=QPixmap("bomb.png");
    qp2=QPixmap("flag.png");

    bombIcon=QIcon(qp1);
    flagIcon=QIcon(qp2);
    setIconSize(QSize(20,20));


}

void Button::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button()==Qt::LeftButton){

        if(status==0){
            status=1;
            if(number==9){
                setStyleSheet("background-color:#A0A0A0;");
                setIcon(bombIcon);
                emit bombFound();
                setDisabled(true);
            }

            else if(number==0){

                emit zeros();
            }

            else{
                setTextColor(QString::number(number));
            }

        }

    }

    if (ev->button()==Qt::RightButton){
        if(status==0){
            flag=true;
            setIcon(flagIcon);
            setStyleSheet("font-size:14px;background-color:#A0A0A0;");
            status=1;
            emit flagMinus();
        }

        else if(status==1 && flag==true){
             setIcon(QIcon());
             setStyleSheet("font-size:14px;background-color:#E0E0E0;");
             status=0;
             flag=false;
             emit flagPlus();
        }
    }

    emit pressed();
}

void Button::setTextColor(const QString &text)
{

    setText(text);

    if(text.compare("1")==0)
        setStyleSheet("color:blue;font-size:14px;background-color:#A0A0A0;");
    if(text.compare("2")==0)
        setStyleSheet("color:green;font-size:14px;background-color:#A0A0A0;");
    if(text.compare("3")==0)
        setStyleSheet("color:red;font-size:14px;background-color:#A0A0A0;");
    if(text.compare("4")==0)
        setStyleSheet("color:yellow;font-size:14px;background-color:#A0A0A0;");
    if(text.compare("5")==0)
        setStyleSheet("color:brown;font-size:14px;background-color:#A0A0A0;");
    if(text.compare("6")==0)
        setStyleSheet("color:orange;font-size:14px;background-color:#A0A0A0;");
    if(text.compare("7")==0)
        setStyleSheet("color:purple;font-size:14px;background-color:#A0A0A0;");
    if(text.compare("8")==0)
        setStyleSheet("color:pink;font-size:14px;background-color:#A0A0A0;");




}


