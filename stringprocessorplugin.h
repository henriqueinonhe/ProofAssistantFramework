#ifndef STRINGPROCESSORPLUGIN_H
#define STRINGPROCESSORPLUGIN_H

#include "pluginfactoryinterface.h"

class StringProcessor;

class StringProcessorPlugin : public PluginFactoryInterface<StringProcessor>
{
public:
    virtual ~StringProcessorPlugin() = 0;

};


Q_DECLARE_INTERFACE(StringProcessorPlugin, "StringProcessorPlugin")

#endif // STRINGPROCESSORPLUGIN_H
