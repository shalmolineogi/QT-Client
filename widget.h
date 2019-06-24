#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>
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
private slots:
    void on_pushButton_clicked();
public slots:
    void readyRead();
    void connected();
    void Write();
    //void data();
    //void

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
};

#endif // WIDGET_H
