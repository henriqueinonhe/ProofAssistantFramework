#ifndef PLUGINFACTORYINTERFACE_H
#define PLUGINFACTORYINTERFACE_H

class Signature;
class InferenceRule;
class InferenceTactic;
class StringProcessor;

template <class T>
class PluginFactoryInterface
{
public:
    virtual T *instance() const = 0;
};

Q_DECLARE_INTERFACE(PluginFactoryInterface<Signature>, "PluginFactoryInterface<Signature>");
Q_DECLARE_INTERFACE(PluginFactoryInterface<const InferenceRule>, "PluginFactoryInterface<const InferenceRule>");
Q_DECLARE_INTERFACE(PluginFactoryInterface<InferenceTactic>, "PluginFactoryInterface<InferenceTactic>");
Q_DECLARE_INTERFACE(PluginFactoryInterface<StringProcessor>, "PluginFactoryInterface<StringProcessor>");

#endif // PLUGINFACTORYINTERFACE_H
