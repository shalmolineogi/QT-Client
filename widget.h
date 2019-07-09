#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>
#include <QThread>
#include <QTcpSocket>
#include <QByteArray>
#include <QMutex>

namespace Ui {
class Widget;
}
//class Widget;
class MyLogger
{
    //Q_OBJECT
public:
    MyLogger();
    void file_write(QString );
//private:
    QString fname = "outputfile.log";
};
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
class Mythread:public QThread
{
    Q_OBJECT
public:
    Mythread(QObject*);
    void run();
private:
    bool f;
    QString amt;
signals:
    void sender();

};


class Widget : public QWidget//,public Logger//, public MyTcpSocket//public Mythread
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void Connect();
    bool getFlag();
    ~Widget();
signals:
        void writer();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    //void on_pushButton_3_clicked();

    //void on_pushButton_4_clicked();

    //void on_pushButton_3_clicked();

    void on_pushButton_3_clicked();

public slots:
    void readyRead();
    void connected();
    void Write();
    void Send();


friend class Mythread;
private:
    Ui::Widget *ui;
    bool b=false;
    MyTcpSocket *socket;
    Mythread *m1,*m2;
    QMutex mutex, mutex1;
};


#endif // WIDGET_H
