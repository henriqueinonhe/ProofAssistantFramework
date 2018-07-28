#ifndef SIGNATUREPLUGIN_H
#define SIGNATUREPLUGIN_H

#include "signature.h"
#include <memory>
#include <QDataStream>

class SignaturePlugin
{
public:
    virtual const Signature *getSignature() const = 0;
    virtual void interfaceWithSignature() = 0;

protected:
    virtual void serialize(QDataStream &stream) const = 0;
    virtual void unserialize(QDataStream &stream) = 0;

    friend QDataStream &operator <<(QDataStream &stream, const SignaturePlugin &signature);
    friend QDataStream &operator >>(QDataStream &stream, SignaturePlugin &signature);
};

QDataStream &operator <<(QDataStream &stream, const SignaturePlugin &signature);
QDataStream &operator >>(QDataStream &stream, SignaturePlugin &signature);

Q_DECLARE_INTERFACE(SignaturePlugin, "SignaturePlugin")

#endif // SIGNATUREPLUGIN_H
