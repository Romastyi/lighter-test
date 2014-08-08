#ifndef LIGHTDIALOG_H
#define LIGHTDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include "parser.h"

namespace Ui {
class LightDialog;
}


class LightDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LightDialog(QWidget *parent = 0);
    ~LightDialog();

    void connectToServer(const QString &host, quint16 port);

public slots:
    void readCommand();
    void socketError(QAbstractSocket::SocketError error);

private slots:
    // Обработчики команд
    // Название метода-обработчика формируется по правилу <Command>_handler(const QByteArray&)
    void On_handler(const QByteArray&);
    void Off_handler(const QByteArray&);
    void Color_handler(const QByteArray &value);

signals:
    // Сигнал о необходимости соединться с сервером заново
    void reconnect();

protected:
    void sendCommand(Parser::Command command, const QByteArray &value);

private:
    Ui::LightDialog *ui;
    QTcpSocket *socket;
};

#endif // LIGHTDIALOG_H
