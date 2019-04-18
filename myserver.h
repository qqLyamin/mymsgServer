#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include <QByteArray>
#include <QDataStream>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject * parent);

signals:

public slots:
    void incoming_connection(); //входящее подключение
    void ready_read();//есть что прочесть
    void state_changed(QAbstractSocket::SocketState);//состояние сетевого соединения
private:
    QTcpServer * server;
    QList<QTcpSocket *> sockets;
    QTcpSocket * firstSocket;
};

#endif // MYSERVER_H
