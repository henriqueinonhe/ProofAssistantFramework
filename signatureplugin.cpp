#include "signatureplugin.h"
#include <QDataStream>

QDataStream &operator <<(QDataStream &stream, const SignaturePlugin &signature)
{
    signature.serialize(stream);

    return stream;
}

QDataStream &operator >>(QDataStream &stream, SignaturePlugin &signature)
{
    signature.unserialize(stream);

    return stream;
}
