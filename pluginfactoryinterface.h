#ifndef PLUGINFACTORYINTERFACE_H
#define PLUGINFACTORYINTERFACE_H

#include <memory>

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

    virtual ~PluginFactoryInterface() = 0;
};

Q_DECLARE_INTERFACE(PluginFactoryInterface<Signature>, "PluginFactoryInterface<Signature>");
Q_DECLARE_INTERFACE(PluginFactoryInterface<const InferenceRule>, "PluginFactoryInterface<const InferenceRule>");
Q_DECLARE_INTERFACE(PluginFactoryInterface<InferenceTactic>, "PluginFactoryInterface<InferenceTactic>");
Q_DECLARE_INTERFACE(PluginFactoryInterface<StringProcessor>, "PluginFactoryInterface<StringProcessor>");

#endif // PLUGINFACTORYINTERFACE_H
