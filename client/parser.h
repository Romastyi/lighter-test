#ifndef PARSER_H
#define PARSER_H

#include <QObject>

class Parser : public QObject
{
    Q_OBJECT
    Q_ENUMS(Command)
public:

    enum Command {
        Invalid = 0,
        On,
        Off,
        Color
    };

    // Тип команды в строку (для обработчика)
    QByteArray commandToChar(Command command);

    // Разбор комнады
    static bool parse(const QByteArray &data, Command &command, QByteArray &value);

};

Q_DECLARE_METATYPE(Parser::Command)

#endif // PARSER_H
