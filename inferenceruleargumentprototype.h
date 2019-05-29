#ifndef INFERENCERULEARGUMENTPROTOTYPE_H
#define INFERENCERULEARGUMENTPROTOTYPE_H

#include <QStringList>

class InferenceRuleArgumentPrototype
{
public:
    enum class ArgumentClass : unsigned int
    {
        LineNumber,
        Parameter,
        Formula,
        Token,
        String
    };

    InferenceRuleArgumentPrototype();
    InferenceRuleArgumentPrototype(const ArgumentClass argumentClass, const QStringList &possibleValues = QStringList());

    ArgumentClass argumentClass;
    QStringList possibleValues;
};

#endif // INFERENCERULEARGUMENTPROTOTYPE_H
