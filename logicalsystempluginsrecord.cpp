#include "logicalsystempluginsrecord.h"
#include <QDataStream>

LogicalSystemPluginsRecord::LogicalSystemPluginsRecord()
{

}

LogicalSystemPluginsRecord::LogicalSystemPluginsRecord(const QStringList &inferenceRulesNamesList, const QString &signatureName) :
    inferenceRulesNamesList(inferenceRulesNamesList),
    signatureName(signatureName)
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


QDataStream &operator <<(QDataStream &stream, const LogicalSystemPluginsRecord &pluginsRecord)
{
    stream << pluginsRecord.inferenceRulesNamesList << pluginsRecord.signatureName;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, LogicalSystemPluginsRecord &pluginsRecord)
{
    stream >> pluginsRecord.inferenceRulesNamesList >> pluginsRecord.signatureName;
    return stream;
}
