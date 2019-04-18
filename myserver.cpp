#include "myserver.h"

MyServer::MyServer(QObject * parent) : QObject (parent), firstSocket(Q_NULLPTR)
{
    server = new QTcpServer(this);
    qDebug() << "server listen " << server->listen(QHostAddress::Any, 30000);
    connect(server, &QTcpServer::newConnection, this, &MyServer::incoming_connection);
}

void MyServer::ready_read() // действия с пришедшим пакетом
{
    QTcpSocket * socket = static_cast<QTcpSocket *>(QObject::sender()); // указатель на QTcpSocet который
                                          // был источником сигнала (отправитель)
    if (!socket)
    {
        return;
    }
    qDebug() << Q_FUNC_INFO << " [1]";

    QByteArray arr = socket->readAll(); //в массив move все из сокета
    //по итогу у нас массив из всех данных сокета

    for(auto soc : sockets)
    {
        if (soc->state()/* запросить состояние сокета*/ == QTcpSocket::ConnectedState)
        {
            //если с ним есть связь
            soc->write(arr);
        }
    }
}

void MyServer::state_changed(QAbstractSocket::SocketState) // изм сост сокета
{
    QTcpSocket * socket = static_cast<QTcpSocket *>(QObject::sender());
    if (!socket)
    {
        return;
        //некого проверять если там 0 указатель
    }
    qDebug() << socket->state();
    if (socket == firstSocket && socket->state() == QAbstractSocket::UnconnectedState)
    {
        socket->deleteLater();
        firstSocket == Q_NULLPTR;
    }
}

void MyServer::incoming_connection() //Обработчик подключений
{
    QTcpSocket * socket = server->nextPendingConnection(); //сокет подключившегося записали
    connect(socket, &QTcpSocket::stateChanged, this, &MyServer::state_changed);
    // взял состояние сокета и передал его серверу в слот state_changed

    if (!firstSocket)
    {
        connect(socket, &QTcpSocket::readyRead, this, &MyServer::ready_read);
        //если наш клиент - первый, то
        //когда сокет даст сигнал о том что есть что читать, MyServer начнет читать
        socket->write("server"); //в сокет пишем строку сервер
        firstSocket = socket;
        qDebug() << "this one is server";
    }
    else {
        socket->write("client");
        sockets.push_back(socket);
    }
}
