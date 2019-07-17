#include "logicalsystempluginsrecord.h"
#include <QDataStream>

LogicalSystemPluginsRecord::LogicalSystemPluginsRecord()
{

}

LogicalSystemPluginsRecord::LogicalSystemPluginsRecord(const QStringList &inferenceRulesNamesList, const QString &signatureName, const QString &proofName) :
    inferenceRulesNamesList(inferenceRulesNamesList),
    signatureName(signatureName),
    proofName(proofName)
{

}

const QStringList &LogicalSystemPluginsRecord::getInferenceRulesNamesList() const
{
    return inferenceRulesNamesList;
}

const QString &LogicalSystemPluginsRecord::getSignatureName() const
{
    return signatureName;
}

const QString &LogicalSystemPluginsRecord::getProofName() const
{
    return proofName;
}

QDataStream &operator <<(QDataStream &stream, const LogicalSystemPluginsRecord &pluginsRecord)
{
    stream << pluginsRecord.inferenceRulesNamesList << pluginsRecord.signatureName << pluginsRecord.proofName;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, LogicalSystemPluginsRecord &pluginsRecord)
{
    stream >> pluginsRecord.inferenceRulesNamesList >> pluginsRecord.signatureName >> pluginsRecord.proofName;
    return stream;
}
