#ifndef STRINGPROCESSORPLUGIN_H
#define STRINGPROCESSORPLUGIN_H

#include "stringprocessor.h"
#include <QDataStream>

class StringProcessorPlugin
{
public:
    const StringProcessor *getStringProcessor() const = 0;

protected:
    virtual void serialize() const = 0;
    virtual void unserialize() = 0;

    friend QDataStream &operator <<(QDataStream &stream, const StringProcessorPlugin &plugin);
    friend QDataStream &operator >>(QDataStream &stream, StringProcessorPlugin &plugin);
};

QDataStream &operator <<(QDataStream &stream, const StringProcessorPlugin &plugin);
QDataStream &operator >>(QDataStream &stream, StringProcessorPlugin &plugin);

#endif // STRINGPROCESSORPLUGIN_H
