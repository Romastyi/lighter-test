#include <QMessageBox>
#include <QTcpSocket>
#include <QScrollBar>
#include "senddialog.h"
#include "ui_senddialog.h"

SendDialog::SendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendDialog), server(new Server)
{
    ui->setupUi(this);
    if (!server->listen(QHostAddress::Any, 9999)) {
        QMessageBox::critical(this, tr("Server error"), tr("Could not start server!"));
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(connectionsChanged()));
}

SendDialog::~SendDialog()
{
    delete server;
    delete ui;
}

bool SendDialog::isStarted() const
{
    return server->isListening();
}

void SendDialog::connectionsChanged()
{
    ui->ConnectionsEdit->clear();
    for (QListIterator<QTcpSocket*> i(server->getConnections()); i.hasNext(); ) {
        const QTcpSocket *socket = i.next();
        QTextCursor cursor(ui->ConnectionsEdit->textCursor());
        cursor.movePosition(QTextCursor::End);
        cursor.insertText(tr("%1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
        QScrollBar *bar = ui->ConnectionsEdit->verticalScrollBar();
        bar->setValue(bar->maximum());
    }
}

void SendDialog::sendCommand(char command, const QByteArray &value)
{
    QByteArray data;
    QDataStream in(&data, QIODevice::WriteOnly);
    in << static_cast<quint8>(command);
    in << static_cast<quint16>(value.length());
    for (int i = 0; i < value.length(); ++i) {
        in << static_cast<quint8>(value.at(i));
    }
    for (QListIterator<QTcpSocket*> i(server->getConnections()); i.hasNext(); ) {
        QTcpSocket *socket = i.next();
        socket->write(data.data(), data.length());
    }
}

void SendDialog::on_OnButton_clicked()
{
    sendCommand(0x12);
}

void SendDialog::on_OffButton_clicked()
{
    sendCommand(0x13);
}

void SendDialog::on_ColorButton_clicked()
{
    sendCommand(0x20, QByteArray::fromHex(ui->ColorEdit->text().toLatin1()));
}

void SendDialog::on_CloseAllButton_clicked()
{
    for (QListIterator<QTcpSocket*> i(server->getConnections()); i.hasNext(); ) {
        i.next()->close();
    }
}
