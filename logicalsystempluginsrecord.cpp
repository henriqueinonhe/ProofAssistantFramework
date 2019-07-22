#include "logicalsystempluginsrecord.h"
#include <QDataStream>

LogicalSystemPluginsRecord::LogicalSystemPluginsRecord()
{

}

LogicalSystemPluginsRecord::LogicalSystemPluginsRecord(const QStringList &inferenceRulesNamesList, const QString &signatureName, const QString &proofName, const QString &proofPrinterPluginName) :
    inferenceRulesNamesList(inferenceRulesNamesList),
    signaturePluginName(signatureName),
    proofPluginName(proofName),
    proofPrinterPluginName(proofPrinterPluginName)
{

}

QStringList LogicalSystemPluginsRecord::getInferenceRulesNamesList() const
{
    return inferenceRulesNamesList;
}

QString LogicalSystemPluginsRecord::getSignaturePluginName() const
{
    return signaturePluginName;
}

QString LogicalSystemPluginsRecord::getProofPluginName() const
{
    return proofPluginName;
}

QString LogicalSystemPluginsRecord::getProofPrinterPluginName() const
{
    return proofPrinterPluginName;
}

QDataStream &operator <<(QDataStream &stream, const LogicalSystemPluginsRecord &pluginsRecord)
{
    stream << pluginsRecord.inferenceRulesNamesList << pluginsRecord.signaturePluginName << pluginsRecord.proofPluginName << pluginsRecord.proofPrinterPluginName;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, LogicalSystemPluginsRecord &pluginsRecord)
{
    stream >> pluginsRecord.inferenceRulesNamesList >> pluginsRecord.signaturePluginName >> pluginsRecord.proofPluginName >> pluginsRecord.proofPrinterPluginName;
    return stream;
}
