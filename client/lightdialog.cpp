#include <QMap>
#include <QHash>
#include <QMessageBox>
#include <QApplication>
#include <QDataStream>
#include <QMetaObject>
#include <QMetaEnum>
#include "lightdialog.h"
#include "ui_lightdialog.h"

LightDialog::LightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LightDialog), socket(new QTcpSocket)
{
    ui->setupUi(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readCommand()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));
    // Первоначальное состояние - OFF
    Off_handler(QByteArray());
}

LightDialog::~LightDialog()
{
    // Закрываем соединение
    socket->close();
    delete socket;
    delete ui;
}

void LightDialog::connectToServer(const QString &host, quint16 port)
{
    socket->abort();
    socket->connectToHost(host, port);
}

void LightDialog::readCommand()
{
    Parser::Command command;
    QByteArray value;

    // Разбриаем поступившую команду
    if(Parser::parse(socket->readAll(), command, value)) {
        // Посылаем комнаду на обработку
        sendCommand(command, value);
    }
}

void LightDialog::socketError(QAbstractSocket::SocketError error)
{
    switch (error) {
    case QAbstractSocket::RemoteHostClosedError: // Соединение закрыто сервером
        if (QMessageBox::question(this, tr("Connection error"),
                                  tr("Connection was closed by server!\nTry to reconnect?")) == QMessageBox::Yes) {
            emit reconnect();
        } else {
            qApp->exit(1);
        }
        break;
    case QAbstractSocket::HostNotFoundError: // Сервер не найден
    case QAbstractSocket::ConnectionRefusedError: // Соединение прервано по таймауту
        if (QMessageBox::question(this, tr("Connection error"),
                                  tr("Server not found!\nTry to reconnect?")) == QMessageBox::Yes) {
            emit reconnect();
        } else {
            qApp->exit(1);
        }
        break;
    default:
        QMessageBox::critical(this, tr("Connection error"), tr("Unknown error: \"%1\"").arg(socket->errorString()));
        break;
    }
}

void LightDialog::sendCommand(Parser::Command command, const QByteArray &value)
{
    // Метод обработчика формируется по правилу <Command>_handler()
    QByteArray methodName(Parser().commandToChar(command));
    methodName.append("_handler");
    // Вызываем метод-обработчик команды
    QMetaObject metaObj = this->staticMetaObject;
    if (!metaObj.invokeMethod(this, methodName.constData(), Qt::DirectConnection, Q_ARG(QByteArray, value))) {
        // Метод не найден
    }
}

// Обработчики команд

class CommandStylesMap : public QMap<Parser::Command, QString>
{
public:
    CommandStylesMap() : QMap<Parser::Command, QString>()
    {
        insert(Parser::On,
               "QLabel#Lighter {"
                   "background-color: green;"
                   "border-style: outset;"
                   "border-width: 2px;"
                   "border-radius: 10px;"
                   "border-color: beige;"
                   "font: bold 14px;"
               "}");
        insert(Parser::Off,
               "QLabel#Lighter {"
                   "background-color: darkgray;"
                   "border-style: outset;"
                   "border-width: 2px;"
                   "border-radius: 10px;"
                   "border-color: beige;"
                   "font: bold 14px;"
               "}");
        insert(Parser::Color,
               "QLabel#Lighter {"
                   "background-color: #%1;"
                   "border-style: outset;"
                   "border-width: 2px;"
                   "border-radius: 10px;"
                   "border-color: beige;"
                   "font: bold 14px;"
               "}");
    }
};
Q_GLOBAL_STATIC(CommandStylesMap, commandStylesMap)

class ComanndStatusMap : public QMap<Parser::Command, QString>
{
public:
    ComanndStatusMap() : QMap<Parser::Command, QString>()
    {
        insert(Parser::On, "ON");
        insert(Parser::Off, "OFF");
        insert(Parser::Color, "COLOR: %1");
    }
};
Q_GLOBAL_STATIC(ComanndStatusMap, comanndStatusMap)

void LightDialog::On_handler(const QByteArray &)
{
    ui->Lighter->setStyleSheet(commandStylesMap()->value(Parser::On));
    ui->Lighter->setText(comanndStatusMap()->value(Parser::On));
}

void LightDialog::Off_handler(const QByteArray &)
{
    ui->Lighter->setStyleSheet(commandStylesMap()->value(Parser::Off));
    ui->Lighter->setText(comanndStatusMap()->value(Parser::Off));
}

void LightDialog::Color_handler(const QByteArray &value)
{
    QString color = QString::fromLatin1(value.toHex());
    ui->Lighter->setStyleSheet(commandStylesMap()->value(Parser::Color).arg(color));
    ui->Lighter->setText(comanndStatusMap()->value(Parser::Color).arg(color));
}
