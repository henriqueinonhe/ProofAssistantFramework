#include "signatureplugin.h"

SignaturePlugin::SignaturePlugin()
{

}

QDataStream &operator <<(QDataStream &stream, const SignaturePlugin &signature)
{
    signature.serialize();

    return stream;
}

QDataStream &operator >>(QDataStream &stream, SignaturePlugin &signature)
{
    signature.unserialize();

    return stream;
}
