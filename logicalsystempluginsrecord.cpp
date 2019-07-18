#include "logicalsystempluginsrecord.h"
#include <QDataStream>

LogicalSystemPluginsRecord::LogicalSystemPluginsRecord()
{

}

LogicalSystemPluginsRecord::LogicalSystemPluginsRecord(const QStringList &inferenceRulesNamesList, const QString &signatureName, const QString &proofName) :
    inferenceRulesNamesList(inferenceRulesNamesList),
    signaturePluginName(signatureName),
    proofPluginName(proofName)
{

}

const QStringList &LogicalSystemPluginsRecord::getInferenceRulesNamesList() const
{
    return inferenceRulesNamesList;
}

const QString &LogicalSystemPluginsRecord::getSignaturePluginName() const
{
    return signaturePluginName;
}

const QString &LogicalSystemPluginsRecord::getProofPluginName() const
{
    return proofPluginName;
}

QDataStream &operator <<(QDataStream &stream, const LogicalSystemPluginsRecord &pluginsRecord)
{
    stream << pluginsRecord.inferenceRulesNamesList << pluginsRecord.signaturePluginName << pluginsRecord.proofPluginName;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, LogicalSystemPluginsRecord &pluginsRecord)
{
    stream >> pluginsRecord.inferenceRulesNamesList >> pluginsRecord.signaturePluginName >> pluginsRecord.proofPluginName;
    return stream;
}
