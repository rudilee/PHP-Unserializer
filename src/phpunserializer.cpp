#include "phpunserializer.h"

PhpUnserializer::PhpUnserializer(QString input) : input(input), index(0)
{
}

QVariant PhpUnserializer::unserialize(QString string)
{
    PhpUnserializer unserializer(string);

    return unserializer.parse();
}

int PhpUnserializer::readLength()
{
    int delimeter = input.indexOf(':', index);
    int length = input.mid(index, delimeter - index).toInt();

    index = delimeter + 2;

    return length;
}

QVariant PhpUnserializer::parse()
{
    QChar type = input.at(index);

    index += 2;

    if (type == 's') {
        return parseString();
    } else if (type == 'i') {
        return parseArithmetic(QMetaType::Int);
    } else if (type == 'd') {
        return parseArithmetic(QMetaType::Double);
    } else if (type == 'b') {
        return parseArithmetic(QMetaType::Int).toInt() == 1;
    } else if (type == 'a') {
        return parseArray();
    } else if (type == 'N') {
        QVariant null;
        null.convert(QMetaType::Int);

        return null;
    } else {
        index -= 2;

        return QVariant();
    }
}

QVariant PhpUnserializer::parseArithmetic(QMetaType::Type type)
{
    int delimeter = input.indexOf(';', index);

    QVariant value(input.mid(index, delimeter - index));
    value.convert(type);

    index = delimeter + 1;

    return value;
}

QString PhpUnserializer::parseString()
{
    int length = readLength();
    QString value = input.mid(index, length);

    index += (length + 2);

    return value;
}

QVariantHash PhpUnserializer::parseArray()
{
    QVariantHash result;
    int length = readLength();

    for (int i = 0; i < length; ++i) {
        QString key = parse().toString();
        QVariant value = parse();

        result.insert(key, value);
    }

    return result;
}
