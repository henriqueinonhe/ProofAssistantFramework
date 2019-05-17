#ifndef SIGNATUREPLUGIN_H
#define SIGNATUREPLUGIN_H

#include "pluginfactoryinterface.h"

class Signature;

class SignaturePlugin : public PluginFactoryInterface<Signature>
{
public:
    virtual ~SignaturePlugin() = 0;
};

Q_DECLARE_INTERFACE(SignaturePlugin, "SignaturePlugin")

#endif // SIGNATUREPLUGIN_H
