#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>
#include <QThread>
#include <QTcpSocket>
#include <QByteArray>
namespace Ui {
class Widget;
}
//class Widget;

class MyTcpSocket:public QTcpSocket
{
    Q_OBJECT
public:
    MyTcpSocket();
//private:
    QByteArray buff;
    QString Size;
//public slots:

};
//class Mythread;
class Mythread:public QThread//,public MyTcpSocket//,public Widget
{
    Q_OBJECT
public:
    Mythread(QString s);
    void run();
private:
    QString name;

signals:
    void writer();
    void sender();
public slots:
    void Write_start();
    void Send_start();

};
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void Connect();
    ~Widget();
signals:

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public slots:
    void readyRead();
    void connected();
    void Write();
    void Send();
    static void Writer_help();
    static void Sender_help();


friend class Mythread;
private:
    Ui::Widget *ui;
    MyTcpSocket *socket;
    Mythread *m1,*m2;
};


#endif // WIDGET_H
