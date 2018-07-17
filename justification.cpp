#include "justification.h"

Justification::Justification()
{

}

Justification::Justification(const QString &inferenceRuleCallCommand, const QStringList &argumentList) :
    inferenceRuleCallCommand(inferenceRuleCallCommand),
    argumentList(argumentList)
{

}

QString Justification::getInferenceRuleCallCommand() const
{
    return inferenceRuleCallCommand;
}

void Justification::setInferenceRuleCallCommand(const QString &value)
{
    inferenceRuleCallCommand = value;
}

QStringList Justification::getArgumentList() const
{
    return argumentList;
}

void Justification::setArgumentList(const QStringList &value)
{
    argumentList = value;
}
