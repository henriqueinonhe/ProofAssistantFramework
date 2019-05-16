#ifndef INFERENCERULEPLUGIN_H
#define INFERENCERULEPLUGIN_H

#include "pluginfactoryinterface.h"

class InferenceRule;

class InferenceRulePlugin : public PluginFactoryInterface<InferenceRule>
{
};

Q_DECLARE_INTERFACE(InferenceRulePlugin, "InferenceRulePlugin")

#endif // INFERENCERULEPLUGIN_H
