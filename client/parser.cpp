#include <QHash>
#include <QByteArray>
#include <QDataStream>
#include <QMetaEnum>
#include "parser.h"

class CommandHash : public QHash<Parser::Command, char>
{
public:
    CommandHash() : QHash<Parser::Command, char>()
    {
        insert(Parser::On, 0x12);
        insert(Parser::Off, 0x13);
        insert(Parser::Color, 0x20);
    }
};
Q_GLOBAL_STATIC(CommandHash, commandHash)

bool Parser::parse(const QByteArray &data, Parser::Command &command, QByteArray &value)
{
    QDataStream in(data);

    // Считываем код команды (поле type - 1 байт)
    quint8 commandCode = 0x00;
    in >> commandCode;
    if ((command = commandHash()->key(commandCode, Invalid)) == Invalid) {
        // Неверный код команды
        return false;
    }

    // Считываем длинну значения (поле length - 2 байта)
    quint16 length = 0;
    in >> length;

    if (length > 0) {
        // Считываем значение (поле value)
        QDataStream out(&value, QIODevice::WriteOnly);
        for (; length > 0 && !in.atEnd(); --length) {
            quint8 v;
            in >> v;
            out << v;
        }
        if (length > 0) {
            // Неверная длинна значения. Без обработки (в задании не уточнено).
            qDebug("Wrong value length.");
        }
    }

    return true;
}


QByteArray Parser::commandToChar(Parser::Command command)
{
    QMetaObject metaObj = this->staticMetaObject;
    QMetaEnum metaEnum = metaObj.enumerator(metaObj.indexOfEnumerator("Command"));
    return metaEnum.key(command);
}
