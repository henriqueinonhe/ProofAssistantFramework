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
class QString;
class Formula;
template <class> class QVector;

template <class T>
class PluginFactoryInterface
{
public:
    virtual shared_ptr<T> instance() const = 0;

    virtual ~PluginFactoryInterface()
    {

    }
};

template <>
class PluginFactoryInterface<Proof>
{
public:
    virtual shared_ptr<Proof> instance(const uint id,
                                       const QString &name,
                                       const QString &description,
                                       const QVector<Formula> &premises,
                                       const Formula &conclusion) const = 0;

    virtual shared_ptr<Proof> instance() const = 0;

    virtual ~PluginFactoryInterface()
    {

    }
};

using SignatureFactoryPlugin = PluginFactoryInterface<Signature>;
using InferenceRuleFactoryPlugin = PluginFactoryInterface<const InferenceRule>;
using InferenceTacticFactoryPlugin = PluginFactoryInterface<const InferenceTactic>;
using StringProcessorFactoryPlugin = PluginFactoryInterface<StringProcessor>;
using ProofFactoryPlugin = PluginFactoryInterface<Proof>;

Q_DECLARE_INTERFACE(SignatureFactoryPlugin, "SignatureFactoryPlugin")
Q_DECLARE_INTERFACE(InferenceRuleFactoryPlugin, "PluginFactoryInterface<const InferenceRule>")
Q_DECLARE_INTERFACE(InferenceTacticFactoryPlugin, "PluginFactoryInterface<const InferenceTactic>")
Q_DECLARE_INTERFACE(StringProcessorFactoryPlugin, "PluginFactoryInterface<StringProcessor>")
Q_DECLARE_INTERFACE(ProofFactoryPlugin, "ProofFactoryPlugin");

#endif // PLUGINFACTORYINTERFACE_H
