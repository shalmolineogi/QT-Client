#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QHostAddress>
#include <QTextStream>
#include <QCoreApplication>
#include <QByteArray>
#include <QChar>
#include <QMutex>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new MyTcpSocket();
    m1 = new Mythread("w");
    m2 = new Mythread("s");
    Connect();
}
MyTcpSocket::MyTcpSocket()
{
}

Mythread::Mythread(QString s)
{
    this->name=s;
    qDebug()<<"Thread tries to Connect signals with slots..";
    connect(this, SIGNAL(writer()),this,SLOT(Write_start()));
    connect(this, SIGNAL(sender()),this,SLOT(Send_start()));
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

}
void Mythread::Write_start()
{
    Widget::Writer_help();
}
void Mythread::Send_start()
{
    Widget::Sender_help();
}
void Widget::Writer_help()
{
    Widget *tmp = new Widget();
    tmp->Write();
}
void Widget::Sender_help()
{
    Widget *tmp = new Widget();
    tmp->Send();
}

void Widget::on_pushButton_clicked()
{
    QString serverip = ui->lineEdit->text();
    QString serverport = ui->lineEdit_2->text();
    QTextStream ts(&serverport);
    quint16 port=0;
    ts>>port;
    socket->connectToHost(serverip,port);
}

void Widget::connected(){
    qDebug() << "Connected";
    //Write();
}

void Widget::readyRead()
{
    qDebug()<<"Socket is reading..";
    QString buff;
    buff.append(socket->readAll());
    qDebug()<<buff;
}
void Widget::Write()
{
    qDebug()<<"Writing started";
    QTextStream ts(&socket->Size);
    int b_size=0;
    ts>>b_size;
    socket->buff=QByteArray(b_size,'a');
    qDebug()<<"Writing finished";
}
void Widget::Send()
{
    qDebug()<<"Sending started";
    socket->write(socket->buff);
    qDebug()<<"Sending finished";
}

void Mythread::run()
{
    if(this->name=="w"){
        qDebug()<<"writer signal emitted";
        emit writer();
    }
    else{
        qDebug()<<"sender signal emitted";
        emit sender();
    }
}
void Widget::on_pushButton_2_clicked()
{

    QMutex mutex;
    //while (1) {
        socket->Size = ui->lineEdit_3->text();
        mutex.lock();
        qDebug()<<"Th1 started";
        m1->start();
        m1->wait();
        mutex.unlock();
        mutex.lock();
        qDebug()<<"Th2 started";
        m2->start();
        m2->wait();
        mutex.unlock();
   // }

}
