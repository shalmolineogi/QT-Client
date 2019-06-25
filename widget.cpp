#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QHostAddress>
#include <QTextStream>
#include <QByteArray>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    Connect();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::Connect()
{
    qDebug()<<"Connecting with slots..";
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(write(short)),this, SLOT(Write(short)));
    connect(socket,SIGNAL(sendData()),this,SLOT(Send(QByteArray)));
}


void Widget::on_pushButton_clicked()
{
    QString serverip = ui->lineEdit->text();
    QString serverport = ui->lineEdit_2->text();
    QTextStream ts(&serverport);
    quint16 port=0;
    ts>>port;
    //qDebug()<<"Connected";
    socket->connectToHost(serverip,port);
}

void Widget::connected(){
    qDebug() << "Connected";
    //socket->write("abcdef");
    //Write();
}

void Widget::readyRead()
{
    qDebug()<<"Socket is reading..";
    QString buff;
    buff.append(socket->readAll());
    qDebug()<<buff;
}
void Widget::Write(short Size)
{
    //int max=Size;
    //QString data;
    QByteArray buff(Size,0);
    QThread *mThread = new QThread;
    mThread->start();
    Send(buff);
    /*max = buff.size();
    //buff.insert(i);
    //QString data=0;
    while(1)
    {
        i++;
        data = QString::number(i);
        qDebug()<<data;
        //buff.append(i);
        if(max >=data.size())
        {
            buff.append(data);
            max = max-data.size();
        }
        else
        {
            socket->write(buff);
            qDebug()<<"Write finshed";
            break;
        }

    }*/
}
void Widget::run()
{
    emit sendData();
}
void Widget::Send(QByteArray buff)
{
    socket->write(buff);
}
void Widget::on_pushButton_2_clicked()
{
    QString Size = ui->lineEdit_3->text();
    QTextStream ts(&Size);
    short b_size=0;
    ts>>b_size;
    Write(b_size);

}
