#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(int mRows,int bombs,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Minesweeper");
    setStyleSheet("background-color:#3F4D41;");
    setFixedSize(300,325);
    this->mRows=mRows;
    this->bombs=bombs;
    this->flags=bombs;



    buttons=QList<Button*>();
    buttons.append(new Button(0,1,1));


    this->matrix=new Matrix* [mRows+2];
    for(int i=0;i<=mRows+1;i++)
        this->matrix[i]=new Matrix [mRows+2];

    for(int i=0;i<=mRows+1;i++){
        for(int j=0;j<=mRows+1;j++){
            this->matrix[i][j].number=0;
            this->matrix[i][j].status=0;
        }
    }


    generateBombs();
    setNumbers();





    led1=new QLCDNumber;
    led1->setStyleSheet("color:green;background-color:white;");
    led1->display(QString::number(flags));


    led2=new QLCDNumber;
    led2->setStyleSheet("color:red;background-color:white;");


    newGame=new QPushButton;
    newGame->setFixedSize(50,50);
    QPixmap qnew("smiley.png");
    icon=QIcon(qnew);

    newGame->setIcon(icon);
    newGame->setIconSize(QSize(50,50));

    QHBoxLayout* horLay=new QHBoxLayout;
    horLay->addWidget(led1);
    horLay->addWidget(newGame);
    horLay->addWidget(led2);


    QVBoxLayout* vertLay=new QVBoxLayout;
    vertLay->addLayout(horLay);




    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(0);
    QWidget *centralWidget = new QWidget;


    connect(newGame,&QPushButton::clicked,this,&MainWindow::restart);

   for(int i=1;i<=mRows;i++){
        for(int j=1;j<=mRows;j++){
            Button* button=new Button(0,i,j);
            button->setStyleSheet("font-size:14px;background-color:#E0E0E0;");
            buttons.append(button);
            button->number=matrix[i][j].number;
            layout->addWidget(button, i, j);
            connect(button,SIGNAL(flagMinus()),this,SLOT(ledMinus()));
            connect(button,SIGNAL(flagPlus()),this,SLOT(ledPlus()));
            connect(button,&Button::bombFound,this,&MainWindow::showBobms);
            connect(button,&Button::pressed,this,&MainWindow::win);

    }
   }

   timer=new MyTimer;
   connect(timer,SIGNAL(timeout()),this,SLOT(changeLed()));


       for(int d=1;d<buttons.size();d++){
           connect(buttons[d],&Button::zeros,this,[&](){
               buttons[d]=qobject_cast<Button *>(sender());
               zeroFields(buttons[d]->row,buttons[d]->column);
           });
       }





       vertLay->addLayout(layout);
       centralWidget->setLayout(vertLay);
       setCentralWidget(centralWidget);



}



void MainWindow::generateBombs(){
    int ct=0,i,j;
    srand(time(0));
    while(ct<bombs){
        i=rand()%mRows+1;
        j=rand()%mRows+1;
        if(matrix[i][j].number==0){
            matrix[i][j].number=9;
            ct++;
        }
    }
}

void MainWindow::setNumbers(){
    for(int i=1;i<=mRows;i++){
        for(int j=1;j<=mRows;j++){
            if(matrix[i][j].number!=9)
                matrix [i][j].number=neighboursSum(i,j);
        }
    }

}

int MainWindow::neighboursSum(int i,int j){
    int sum=0;
    sum+=matrix[i-1][j-1].number==9;
    sum+=matrix[i-1][j].number==9;
    sum+=matrix[i-1][j+1].number==9;
    sum+=matrix[i][j-1].number==9;
    sum+=matrix[i][j+1].number==9;
    sum+=matrix[i+1][j-1].number==9;
    sum+=matrix[i+1][j].number==9;
    sum+=matrix[i+1][j+1].number==9;

    return sum;
}

void MainWindow::printMatrix(){
    for(int i=1;i<=mRows;i++){
        QString sor;
        for(int j=1;j<=mRows;j++){
            sor.append(QString::number(matrix[i][j].number)+" ");
        }
        qDebug()<<sor;
    }
}

void MainWindow::showBobms()
{

    for(int i=1;i<buttons.size();i++){

        if(buttons[i]->number==9){
            buttons[i]->setIcon(buttons[i]->bombIcon);            
        }

        else {
            buttons[i]->setIcon(QIcon());
            if(buttons[i]->number!=0)
                buttons[i]->setTextColor(QString::number(buttons[i]->number));
            else
                buttons[i]->setText("");
        }
        buttons[i]->setDisabled(true);


    }

    timer->stop();

}



void MainWindow::restart()
{

    timer->stop();
    led2->display("0");


    buttons=QList<Button*>();
    buttons.append(new Button(0,1,1));



    setStyleSheet("background-color:#3F4D41;");
    setFixedSize(300,325);
    this->flags=bombs;

    this->matrix=new Matrix* [mRows+2];
    for(int i=0;i<=mRows+1;i++)
        this->matrix[i]=new Matrix [mRows+2];

    for(int i=0;i<=mRows+1;i++){
        for(int j=0;j<=mRows+1;j++){
            this->matrix[i][j].number=0;
            this->matrix[i][j].status=0;
        }
    }


    generateBombs();
    setNumbers();




    led1=new QLCDNumber;
    led1->setStyleSheet("color:green;background-color:white;");

    led1->display(QString::number(flags));


    led2=new QLCDNumber;
    led2->setStyleSheet("color:red;background-color:white;");


    newGame=new QPushButton;
    newGame->setFixedSize(50,50);
    QPixmap qnew("smiley.png");
    icon=QIcon(qnew);

    newGame->setIcon(icon);
    newGame->setIconSize(QSize(50,50));

    QHBoxLayout* horLay=new QHBoxLayout;
    horLay->addWidget(led1);
    horLay->addWidget(newGame);
    horLay->addWidget(led2);


    QVBoxLayout* vertLay=new QVBoxLayout;
    vertLay->addLayout(horLay);



    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(0);
    QWidget *centralWidget = new QWidget;


    connect(newGame,&QPushButton::clicked,this,&MainWindow::restart);

   for(int i=1;i<=mRows;i++){
        for(int j=1;j<=mRows;j++){
            Button* button=new Button(0,i,j);
            button->setStyleSheet("font-size:14px;background-color:#E0E0E0;");
            buttons.append(button);
            button->number=matrix[i][j].number;
            layout->addWidget(button, i, j);
            connect(button,SIGNAL(flagMinus()),this,SLOT(ledMinus()));
            connect(button,SIGNAL(flagPlus()),this,SLOT(ledPlus()));
            connect(button,&Button::bombFound,this,&MainWindow::showBobms);
            connect(button,&Button::pressed,this,&MainWindow::win);

    }
   }

   timer=new MyTimer;
   connect(timer,SIGNAL(timeout()),this,SLOT(changeLed()));


       for(int d=1;d<buttons.size();d++){
           connect(buttons[d],&Button::zeros,this,[&](){
               buttons[d]=qobject_cast<Button *>(sender());
               zeroFields(buttons[d]->row,buttons[d]->column);
           });
       }




       vertLay->addLayout(layout);
       centralWidget->setLayout(vertLay);
       setCentralWidget(centralWidget);



}




Button* MainWindow::getButton(int i,int j){
    for(int d=1;d<buttons.size();d++){
        if(buttons[d]->row==i && buttons[d]->column==j)
            return buttons[d];
    }
    return nullptr;
}

void MainWindow::zeroFields(int i, int j)
{


    if(i>=1 && i<=mRows && j>=1 && j<=mRows){


        getButton(i,j)->status=1;
         getButton(i,j)->setStyleSheet("font-size:14px;background-color:#A0A0A0;");


         matrix[i][j].status=1;

        showNeighbours(i,j);


        if(matrix[i-1][j-1].number==0 && matrix[i-1][j-1].status==0)
            zeroFields(i-1,j-1);

        if(matrix[i-1][j].number==0 && matrix[i-1][j].status==0)
            zeroFields(i-1,j);

      if(matrix[i-1][j+1].number==0 && matrix[i-1][j+1].status==0)
            zeroFields(i-1,j+1);

        if(matrix[i][j-1].number==0 && matrix[i][j-1].status==0)
            zeroFields(i,j-1);

        if(matrix[i][j+1].number==0 && matrix[i][j+1].status==0)
         zeroFields(i,j+1);

        if(matrix[i+1][j-1].number==0 && matrix[i+1][j-1].status==0)
         zeroFields(i+1,j-1);

        if(matrix[i+1][j].number==0 && matrix[i+1][j].status==0)
            zeroFields(i+1,j);

       if(matrix[i+1][j+1].number==0 && matrix[i+1][j+1].status==0)
           zeroFields(i+1,j+1);
   }
}

void MainWindow::showNeighbours(int i,int j)
{
    if(matrix[i-1][j-1].number>0 && matrix[i-1][j-1].number<9 && matrix[i-1][j-1].status==0){
        getButton(i-1,j-1)->setTextColor(QString::number(matrix[i-1][j-1].number));
        getButton(i-1,j-1)->status=1;      
        matrix[i-1][j-1].status=1;
    }
    if(matrix[i-1][j].number>0 && matrix[i-1][j].number<9 && matrix[i-1][j].status==0){
        getButton(i-1,j)->setTextColor(QString::number(matrix[i-1][j].number));
        getButton(i-1,j)->status=1;
        matrix[i-1][j].status=1;
    }
    if(matrix[i-1][j+1].number>0 && matrix[i-1][j+1].number<9 && matrix[i-1][j+1].status==0){
        getButton(i-1,j+1)->setTextColor(QString::number(matrix[i-1][j+1].number));
        getButton(i-1,j+1)->status=1;
        matrix[i-1][j+1].status=1;
    }
    if(matrix[i][j-1].number>0 && matrix[i][j-1].number<9 && matrix[i][j-1].status==0){
        getButton(i,j-1)->setTextColor(QString::number(matrix[i][j-1].number));
        getButton(i,j-1)->status=1;
        matrix[i][j-1].status=1;
    }
    if(matrix[i][j+1].number>0 && matrix[i][j+1].number<9 && matrix[i][j+1].status==0){
        getButton(i,j+1)->setTextColor(QString::number(matrix[i][j+1].number));
        getButton(i,j+1)->status=1;
        matrix[i][j+1].status=1;
    }
    if(matrix[i+1][j-1].number>0 && matrix[i+1][j-1].number<9 && matrix[i+1][j-1].status==0){
        getButton(i+1,j-1)->setTextColor(QString::number(matrix[i+1][j-1].number));
        getButton(i+1,j-1)->status=1;
        matrix[i+1][j-1].status=1;
    }
    if(matrix[i+1][j].number>0 && matrix[i+1][j].number<9 && matrix[i+1][j].status==0){
       getButton(i+1,j)->setTextColor(QString::number(matrix[i+1][j].number));
       getButton(i+1,j)->status=1;
       matrix[i+1][j].status=1;
    }
    if(matrix[i+1][j+1].number>0 && matrix[i+1][j+1].number<9 && matrix[i+1][j+1].status==0){
       getButton(i+1,j+1)->setTextColor(QString::number(matrix[i+1][j+1].number));
       getButton(i+1,j+1)->status=1;
       matrix[i+1][j+1].status=1;
    }

    updateStatus();

}

void  MainWindow::win()
{

    int ct=0;

    updateStatus();



    for(int i=1;i<buttons.size();i++){
        if(buttons[i]->number!=9 && buttons[i]->status==1 && buttons[i]->flag==false)
            ct++;
    }


    if(ct==mRows*mRows-bombs){
        timer->stop();
        for(int i=1;i<buttons.size();i++){
            if(buttons[i]->number==9){
                buttons[i]->setIcon(buttons[i]->bombIcon);
            }
            buttons[i]->setDisabled(true);            
        }


        QMessageBox::about(0,"End","WIN!");

    }
}

void MainWindow::printStatus()
{
    for(int i=0;i<=mRows;i++){
        QString sor;
        for(int j=1;j<=mRows;j++){
            sor.append(QString::number(matrix[i][j].status)+" ");
        }
        qDebug()<<sor;
    }
}

void MainWindow::ledPlus()
{
    flags++;
    led1->display(QString::number(flags));
}

void MainWindow::ledMinus()
{
    flags--;
    led1->display(QString::number(flags));
}

void MainWindow::changeLed()
{
    led2->display(QString::number(timer->ct));
    timer->ct++;

}



void MainWindow::updateStatus(){
    for(int i=1;i<buttons.size();i++){
        matrix[buttons[i]->row][buttons[i]->column].status=buttons[i]->status;
    }
}





MainWindow::~MainWindow()
{
    delete ui;
}

