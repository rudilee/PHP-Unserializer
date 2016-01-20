#include <QString>
#include <QtTest>

#include "phpunserializer.h"

class PhpUnserializerTest : public QObject
{
    Q_OBJECT

public:
    PhpUnserializerTest();

private Q_SLOTS:
    void testUnserializeString();
    void testUnserializeInteger();
    void testUnserializeFloat();
    void testUnserializeBoolean();
    void testUnserializeNull();
    void testUnserializeArray();
};

PhpUnserializerTest::PhpUnserializerTest()
{
}

void PhpUnserializerTest::testUnserializeString()
{
    QString serialized = "s:19:\"this is test string\";";
    QString unserialized = PhpUnserializer::unserialize(serialized).toString();

    QCOMPARE(unserialized, QString("this is test string"));
}

void PhpUnserializerTest::testUnserializeInteger()
{
    QString serialized = "i:12345;";
    int unserialized = PhpUnserializer::unserialize(serialized).toInt();

    QCOMPARE(unserialized, 12345);
}

void PhpUnserializerTest::testUnserializeFloat()
{
    QString serialized = "d:12345.678;";
    double unserialized = PhpUnserializer::unserialize(serialized).toDouble();

    QCOMPARE(unserialized, 12345.678);
}

void PhpUnserializerTest::testUnserializeBoolean()
{
    QString serialized = "b:1;";
    bool unserialized = PhpUnserializer::unserialize(serialized).toBool();

    QCOMPARE(unserialized, true);
}

void PhpUnserializerTest::testUnserializeNull()
{
    QString serialized = "N;";

    QVERIFY(!PhpUnserializer::unserialize(serialized).isValid());
}

void PhpUnserializerTest::testUnserializeArray()
{
    QString serialized = "a:7:{s:6:\"string\";s:19:\"this is test string\";i:0;s:19:\"another test string\";s:7:\"integer\";i:12345;s:5:\"float\";d:12345.678;s:7:\"boolean\";b:1;s:4:\"null\";N;s:5:\"array\";a:2:{i:0;s:21:\"yet other test string\";s:4:\"test\";i:123;}}";
    QVariantHash unserialized = PhpUnserializer::unserialize(serialized).toHash();

    QVariantHash expected;
    expected["string"] = QString("this is test string");
    expected["0"] = QString("another test string");
    expected["integer"] = 12345;
    expected["float"] = 12345.678;
    expected["boolean"] = true;
    expected["null"] = QVariant();

    QVariantHash array;
    array["0"] = "yet other test string";
    array["test"] = 123;

    expected["array"] = array;

    QCOMPARE(unserialized, expected);
}

QTEST_APPLESS_MAIN(PhpUnserializerTest)

#include "phpunserializertest.moc"
