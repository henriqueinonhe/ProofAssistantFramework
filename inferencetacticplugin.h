#ifndef INFERENCETACTICPLUGIN_H
#define INFERENCETACTICPLUGIN_H

#include "pluginfactoryinterface.h"

class InferenceTactic;

class InferenceTacticPlugin : public PluginFactoryInterface<InferenceTactic>
{
public:
    virtual ~InferenceTacticPlugin() = 0;
};

Q_DECLARE_INTERFACE(InferenceTacticPlugin, "InferenceTacticPluin")

#endif // INFERENCETACTICPLUGIN_H
