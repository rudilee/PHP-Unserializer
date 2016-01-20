#ifndef PHPUNSERIALIZER_H
#define PHPUNSERIALIZER_H

#include <QString>
#include <QVariant>
#include <QMetaType>
#include <QVariantHash>

class PhpUnserializer
{
public:
    explicit PhpUnserializer(QString input);
    static QVariant unserialize(QString string);

private:
    QString input;
    int index;

    int readLength();
    QVariant parse();
    QVariant parseArithmetic(QMetaType::Type type);
    QString parseString();
    QVariantHash parseArray();
};

#endif // PHPUNSERIALIZER_H
