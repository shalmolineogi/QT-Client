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
#include <QFile>

MyLogger mylog;
QFile file(mylog.fname);
int c=0;
//Mythread *fl= new Mythread(QObject *p);
bool flag=false;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    mylog.file_write("Widget_constructor\n");
    ui->setupUi(this);
    socket = new MyTcpSocket();

    Connect();
}
MyTcpSocket::MyTcpSocket()
{
    mylog.file_write("MyTcpSocket_constructor\n");
}

Mythread::Mythread(QObject* p)
{
    mylog.file_write("MyThread_constructor\n");
    //Widget *p1;
    //p1=(Widget*)p;
    //this->f=p1->getFlag();
    //this->name=s;
    qDebug()<<"Thread tries to Connect signals with slots..";

    connect(this, SIGNAL(sender()),p,SLOT(Send()));
    qDebug()<<"Thread finished Connecting signals with slots..";
}

Widget::~Widget()
{
    mylog.file_write("Widget_destructor\n");
    delete ui;
}
void Widget::Connect()
{
    mylog.file_write("Connect\n");
    qDebug()<<"Connecting with slots..";
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(this, SIGNAL(writer()),this,SLOT(Write()));
}

void Widget::on_pushButton_clicked()
{
    //ui->pushButton_2->enabledChange();
    mylog.file_write("pushbutton1\n");
    QString serverip = ui->lineEdit->text();
    QString serverport = ui->lineEdit_2->text();
    QTextStream ts(&serverport);
    quint16 port=0;
    ts>>port;
    qDebug()<<port;
    socket->connectToHost(serverip,port);
}

void Widget::connected(){
    mylog.file_write("connected\n");
    qDebug() << "Connected";
    //Write();
}

void Widget::readyRead()
{
    mylog.file_write("readyread\n");
    qDebug()<<"Socket is reading..";
    QString buff;
    buff.append(socket->readAll());
    qDebug()<<buff;
}
void Widget::Write()
{
    mylog.file_write("Write\n");
    mutex.lock();
    qDebug()<<"Writing started";
    socket->buff=QByteArray(socket->Size.toInt(),'b');
    qDebug()<<socket->buff.size();
    QString s_data = QString::fromAscii(socket->buff.data());
    qDebug()<<s_data;
    qDebug()<<"Writing finished";
    mutex.unlock();
}
void Widget::Send()
{
    mylog.file_write("Send\n");
    mutex.lock();c++;
    qDebug()<<"Sending started"<<c;
    QString s_data = QString::fromAscii(socket->buff.data());
    qDebug()<<s_data;
    qDebug()<<socket->buff.size();
    //while(flag){
        socket->write(socket->buff);
    //}
    qDebug()<<"Sending finished"<<c;
    mutex.unlock();
}

void Mythread::run()
{
    mylog.file_write("run\n");
    //else{
    //QMutex mu1;
    int n=1;
    n<<=23;
       while (n) {
         //
           // mu1.lock();
            qDebug()<<"sender signal emitted"<<n;
            emit sender();
            //this->sleep(5);
            n--;
            //qDebug()<<"sender signal emitted";
            //emit sender();
            //mu1.unlock();
       }

    //}
}
void Widget::on_pushButton_2_clicked()
{

    mylog.file_write("pushbutton2\n");

        socket->Size = ui->lineEdit_3->text();
        //qDebug()<<"Th1 started";
        //m1 = new Mythread("w",this);
        qDebug()<<"writer signal emitted";
        emit writer();

        //this->b=true;
        flag=true;
        qDebug()<<flag;
        mutex1.lock();
        qDebug()<<"Th2 started";
        m2 = new Mythread(this);
        //while (flag) {
        m2->start();
        m2->wait();
        //}

        mutex1.unlock();

}
MyLogger::MyLogger(){


}
void MyLogger::file_write(QString str){

        // Trying to open in WriteOnly and Text mode
        if(!file.open(QFile::WriteOnly |
                      QFile::Append))
        {
            qDebug() << " Could not open file for writing";
            return;
        }

        QTextStream out(&file);
        out << str;
        file.flush();
        file.close();

}
/*bool Widget::getFlag(){
    mylog.file_write("getFlag\n");
    return this->b;
}*/


void Widget::on_pushButton_3_clicked()
{
    mylog.file_write("Stop\n");
    flag=false;
    qDebug()<<flag;
}
