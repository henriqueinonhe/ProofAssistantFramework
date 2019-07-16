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

QStringList LogicalSystemPluginsRecord::getInferenceRulesNamesList() const
{
    return inferenceRulesNamesList;
}

void LogicalSystemPluginsRecord::setInferenceRulesNamesList(const QStringList &value)
{
    inferenceRulesNamesList = value;
}

QString LogicalSystemPluginsRecord::getSignatureName() const
{
    return signatureName;
}

void LogicalSystemPluginsRecord::setSignatureName(const QString &value)
{
    signatureName = value;
}

QString LogicalSystemPluginsRecord::getProofName() const
{
    return proofName;
}

void LogicalSystemPluginsRecord::setProofName(const QString &value)
{
    proofName = value;
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
