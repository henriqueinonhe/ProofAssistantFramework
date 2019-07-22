#include "justification.h"
#include <QDataStream>
#include "qtclassesdeserialization.h"

Justification::Justification(QDataStream &stream) :
    inferenceRuleCallCommand(QtDeserialization::deserializeQString(stream)),
    argumentList(QtDeserialization::deserializeQStringList(stream))
{
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

const QString &Justification::getInferenceRuleCallCommand() const
{
    return inferenceRuleCallCommand;
}

const QStringList &Justification::getArgumentList() const
{
    return argumentList;
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
