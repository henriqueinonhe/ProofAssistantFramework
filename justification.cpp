#include "justification.h"
#include <QDataStream>

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

QDataStream &operator <<(QDataStream &stream, const Justification &justification)
{
    stream << justification.inferenceRuleCallCommand << justification.argumentList;
}

QDataStream &operator >>(QDataStream &stream, Justification &justification)
{
    stream >> justification.inferenceRuleCallCommand >> justification.argumentList;
}
