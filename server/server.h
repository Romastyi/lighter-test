#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);

    QList<QTcpSocket*> getConnections() const;

protected slots:
    void deleteConnection();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QList<QTcpSocket*> connections;
};

#endif // SERVER_H
