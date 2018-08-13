#ifndef STRINGPROCESSORPLUGIN_H
#define STRINGPROCESSORPLUGIN_H

#include "stringprocessor.h"
#include <QDataStream>

class StringProcessorPlugin : virtual public StringProcessor
{
public:
    virtual QString processString(const QString &string) const = 0;
    virtual QString toString() const = 0;

protected:
    virtual void serialize(QDataStream &stream) const = 0;
    virtual void unserialize(QDataStream &stream) = 0;

    friend QDataStream &operator <<(QDataStream &stream, const StringProcessorPlugin &plugin);
    friend QDataStream &operator >>(QDataStream &stream, StringProcessorPlugin &plugin);

};

QDataStream &operator <<(QDataStream &stream, const StringProcessorPlugin &plugin);
QDataStream &operator >>(QDataStream &stream, StringProcessorPlugin &plugin);

Q_DECLARE_INTERFACE(StringProcessorPlugin, "StringProcessorPlugin")

#endif // STRINGPROCESSORPLUGIN_H
