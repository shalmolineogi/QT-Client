#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>
#include <QThread>
namespace Ui {
class Widget;
}
class QTcpSocket;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void Connect();
    ~Widget();
signals:
    void write(short);
    void sendData();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public slots:
    void readyRead();
    void connected();
    void Write(short);
    void run();
    void Send(QByteArray);
    //void data();
    //void

private:
    Ui::Widget *ui;
    QTcpSocket *socket;

};

#endif // WIDGET_H
