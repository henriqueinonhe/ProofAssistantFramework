#ifndef PLUGINFACTORYINTERFACE_H
#define PLUGINFACTORYINTERFACE_H

#include <memory>
#include <QtPlugin>

using namespace std;

class Signature;
class InferenceRule;
class InferenceTactic;
class StringProcessor;

template <class T>
class PluginFactoryInterface
{
public:
    virtual shared_ptr<T> instance() const = 0;

    virtual ~PluginFactoryInterface()
    {

    }
};

typedef PluginFactoryInterface<Signature> SignatureFactoryPlugin;
typedef PluginFactoryInterface<const InferenceRule> InferenceRuleFactoryPlugin;
typedef PluginFactoryInterface<InferenceTactic> InferenceTacticFactoryPlugin;
typedef PluginFactoryInterface<StringProcessor> StringProcessorFactoryPlugin;

Q_DECLARE_INTERFACE(SignatureFactoryPlugin, "SignatureFactoryPlugin")
Q_DECLARE_INTERFACE(InferenceRuleFactoryPlugin, "PluginFactoryInterface<const InferenceRule>")
Q_DECLARE_INTERFACE(InferenceTacticFactoryPlugin, "PluginFactoryInterface<InferenceTactic>")
Q_DECLARE_INTERFACE(StringProcessorFactoryPlugin, "PluginFactoryInterface<StringProcessor>")

#endif // PLUGINFACTORYINTERFACE_H
