#ifndef TCP_H
#define TCP_H

#include <QTimer>
#include <QTcpSocket>
#include <QTcpServer>
using std::vector;

extern vector<QString> cache;


class Tcp:public QObject
{
    Q_OBJECT
public:
    Tcp();

    void dealInfo(int id,QString info);
    void sendInfo(int id,QString name,int num);
    void sendInfo(int id,QString name,int num1,int num2);
    void sendInfo(int id,QString name,QString info);
    void sendInfo(int id,QString name,QString info1,QString info2);
    void sendInfoStr(int id,QString name,QString info);

    QTcpServer *server;
    vector<QTcpSocket*> socket;
    QTimer mytime;
    QTimer myheart;
    int myPort;

signals:
    void tcpNewConnectionAdd();
    void tcpReceiveInfo(QString info);
    void tcpConnectSuccess();

public slots:
    void newConnection();
    void connectionLost();
    void sendInfo(int id,QString info);
    void receiveInfo(int id);
    void makeServer();
};

extern Tcp *tcp;
#endif // TCP_H
