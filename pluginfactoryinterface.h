#ifndef PLUGINFACTORYINTERFACE_H
#define PLUGINFACTORYINTERFACE_H

#include <memory>
#include <QtPlugin>

using namespace std;

class Signature;
class InferenceRule;
class InferenceTactic;
class StringProcessor;
class Proof;

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
typedef PluginFactoryInterface<const InferenceTactic> InferenceTacticFactoryPlugin;
typedef PluginFactoryInterface<StringProcessor> StringProcessorFactoryPlugin;
typedef PluginFactoryInterface<Proof> ProofFactoryPlugin;

Q_DECLARE_INTERFACE(SignatureFactoryPlugin, "SignatureFactoryPlugin")
Q_DECLARE_INTERFACE(InferenceRuleFactoryPlugin, "PluginFactoryInterface<const InferenceRule>")
Q_DECLARE_INTERFACE(InferenceTacticFactoryPlugin, "PluginFactoryInterface<const InferenceTactic>")
Q_DECLARE_INTERFACE(StringProcessorFactoryPlugin, "PluginFactoryInterface<StringProcessor>")
Q_DECLARE_INTERFACE(ProofFactoryPlugin, "ProofFactoryPlugin");

#endif // PLUGINFACTORYINTERFACE_H
