#ifndef SIGNATUREPLUGIN_H
#define SIGNATUREPLUGIN_H

#include "signature.h"
#include <memory>
#include <QDataStream>

class SignaturePlugin
{
public:
    SignaturePlugin();

    virtual const Signature *getSignature() const = 0;
    virtual void interfaceWithSignature() = 0;

protected:
    virtual void serialize() const = 0;
    virtual void unserialize() = 0;

    friend QDataStream &operator <<(QDataStream &stream, const SignaturePlugin &signature);
    friend QDataStream &operator >>(QDataStream &stream, SignaturePlugin &signature);
};

QDataStream &operator <<(QDataStream &stream, const SignaturePlugin &signature);
QDataStream &operator >>(QDataStream &stream, SignaturePlugin &signature);

#endif // SIGNATUREPLUGIN_H
