#include "justification.h"
#include <QDataStream>

Justification::Justification(QDataStream &stream)
{
    stream >> *this;
}

Justification::Justification(const QString &inferenceRuleCallCommand, const QStringList &argumentList) :
    inferenceRuleCallCommand(inferenceRuleCallCommand),
    argumentList(argumentList)
{

}

bool Justification::operator==(const Justification &other) const
{
    return this->argumentList == other.argumentList &&
           this->inferenceRuleCallCommand == other.inferenceRuleCallCommand;
}

bool Justification::operator!=(const Justification &other) const
{
    return !(*this == other);
}

QString Justification::getInferenceRuleCallCommand() const
{
    return inferenceRuleCallCommand;
}

QStringList Justification::getArgumentList() const
{
    return argumentList;
}

Justification::Justification()
{

}

QDataStream &operator <<(QDataStream &stream, const Justification &justification)
{
    stream << justification.inferenceRuleCallCommand << justification.argumentList;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Justification &justification)
{
    stream >> justification.inferenceRuleCallCommand >> justification.argumentList;
    return stream;
}
