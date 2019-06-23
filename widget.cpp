#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QHostAddress>
#include <QTextStream>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
}

Widget::~Widget()
{
    delete ui;
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
    if(socket->waitForConnected(3000)){
        qDebug()<<"Connected";
        socket->close();
    }
    else {
        qDebug()<<"Not Connected";
    }
}

