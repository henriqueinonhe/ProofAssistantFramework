#include "stringprocessorplugin.h"

QDataStream &operator <<(QDataStream &stream, const StringProcessorPlugin &plugin)
{
    plugin.serialize(stream);

    return stream;
}

QDataStream &operator >>(QDataStream &stream, StringProcessorPlugin &plugin)
{
    plugin.unserialize(stream);

    return stream;
}
