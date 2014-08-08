#include <QtTest>
#include "../client/parser.h"

class TestParser : public QObject
{
    Q_OBJECT
public:
    TestParser() : QObject() { }

private slots:
    void testCommandToChar_data()
    {
        QTest::addColumn<Parser::Command>("command");
        QTest::addColumn<QByteArray>("str");

        QTest::newRow("1) Invalid") << Parser::Invalid << QByteArray("Invalid");
        QTest::newRow("2) On")      << Parser::On      << QByteArray("On");
        QTest::newRow("3) Off")     << Parser::Off     << QByteArray("Off");
        QTest::newRow("4) Color")   << Parser::Color   << QByteArray("Color");
    }

    void testCommandToChar()
    {
        QFETCH(Parser::Command, command);
        QFETCH(QByteArray, str);

        QCOMPARE(Parser().commandToChar(command), str);
    }

    void testParse_data()
    {
        QTest::addColumn<bool>("res");
        QTest::addColumn<QByteArray>("data");
        QTest::addColumn<Parser::Command>("command");
        QTest::addColumn<int>("length");
        QTest::addColumn<QByteArray>("value");

        QByteArray data;
        QDataStream in1(&data, QIODevice::WriteOnly);
        in1 << static_cast<quint8>(0x00);
        in1 << static_cast<quint16>(0);
        QTest::newRow("1.1) Invalid command") << false << data << Parser::Invalid << 0 << QByteArray();
        data.clear();
        QDataStream in2(&data, QIODevice::WriteOnly);
        in2 << static_cast<quint8>(0x01);
        in2 << static_cast<quint16>(0);
        QTest::newRow("1.2) Invalid command") << false << data << Parser::Invalid << 0 << QByteArray();
        data.clear();
        QDataStream in3(&data, QIODevice::WriteOnly);
        in3 << static_cast<quint8>(0x12);
        in3 << static_cast<quint16>(0);
        QTest::newRow("2) Ok command") << true << data << Parser::On << 0 << QByteArray();
        data.clear();
        QDataStream in4(&data, QIODevice::WriteOnly);
        in4 << static_cast<quint8>(0x13);
        in4 << static_cast<quint16>(0);
        QTest::newRow("3) Off command") << true << data << Parser::Off << 0 << QByteArray();
        data.clear();
        QDataStream in5(&data, QIODevice::WriteOnly);
        in5 << static_cast<quint8>(0x20);
        in5 << static_cast<quint16>(0);
        QTest::newRow("3.1) Color command") << true << data << Parser::Color << 0 << QByteArray();
        data.clear();
        QDataStream in6(&data, QIODevice::WriteOnly);
        in6 << static_cast<quint8>(0x20);
        in6 << static_cast<quint16>(3);
        in6 << static_cast<quint8>(0xFF);
        in6 << static_cast<quint8>(0xCC);
        in6 << static_cast<quint8>(0xDD);
        QTest::newRow("3.2) Color command") << true << data << Parser::Color << 3 << QByteArray::fromHex("ffccdd");
        data.clear();
        QDataStream in7(&data, QIODevice::WriteOnly);
        in7 << static_cast<quint8>(0x20);
        in7 << static_cast<quint16>(3);
        in7 << static_cast<quint8>(0x00);
        in7 << static_cast<quint8>(0xCC);
        QTest::newRow("3.3) Color command") << true << data << Parser::Color << 2 << QByteArray::fromHex("00cc");
        QDataStream in8(&data, QIODevice::WriteOnly);
        in8 << static_cast<quint8>(0x20);
        in8 << static_cast<quint16>(3);
        in8 << static_cast<quint8>(0x00);
        in8 << static_cast<quint8>(0xCC);
        in8 << static_cast<quint8>(0xDD);
        QTest::newRow("3.4) Color command") << true << data << Parser::Color << 3 << QByteArray::fromHex("00ccdd");
    }

    void testParse()
    {
        QFETCH(bool, res);
        QFETCH(QByteArray, data);
        QFETCH(Parser::Command, command);
        QFETCH(int, length);
        QFETCH(QByteArray, value);

        bool res1;
        Parser::Command command1;
        QByteArray value1;
        QCOMPARE((res1 = Parser::parse(data, command1, value1)), res);
        QCOMPARE(command1, command);
        QCOMPARE(value.length(), length);
        QCOMPARE(value1, value);
    }

};

QTEST_MAIN(TestParser)

#include "main.moc"

