#include "inferenceruleargumentprototype.h"

InferenceRuleArgumentPrototype::InferenceRuleArgumentPrototype()
{

}

InferenceRuleArgumentPrototype::InferenceRuleArgumentPrototype(const InferenceRuleArgumentPrototype::ArgumentClass argumentClass, const QStringList &possibleValues) :
    argumentClass(argumentClass),
    possibleValues(possibleValues)
{

}
