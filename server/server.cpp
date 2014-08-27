#include "server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
}

QList<QTcpSocket *> Server::getConnections() const
{
    return connections;
}

void Server::deleteConnection()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    connections.removeAll(socket);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteConnection()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(newConnection()));
    connections << socket;
}
