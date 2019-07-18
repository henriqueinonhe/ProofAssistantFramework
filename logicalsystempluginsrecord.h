#ifndef LOGICALSYSTEMPLUGINSRECORD_H
#define LOGICALSYSTEMPLUGINSRECORD_H

#include <QString>
#include <QStringList>

class QDataStream;

struct LogicalSystemPluginsRecord
{
public:
    LogicalSystemPluginsRecord();
    LogicalSystemPluginsRecord(const QStringList &inferenceRulesNamesList, const QString &signaturePluginName, const QString &proofPluginName);

    const QStringList &getInferenceRulesNamesList() const;
    const QString &getSignaturePluginName() const;
    const QString &getProofPluginName() const;

    QStringList inferenceRulesNamesList;
    QString signaturePluginName;
    QString proofPluginName;

    friend QDataStream &operator << (QDataStream &, const LogicalSystemPluginsRecord &);
    friend QDataStream &operator >> (QDataStream &, LogicalSystemPluginsRecord &);
};

QDataStream &operator << (QDataStream &stream, const LogicalSystemPluginsRecord &pluginsRecord);
QDataStream &operator >> (QDataStream &stream, LogicalSystemPluginsRecord &pluginsRecord);

#endif // LOGICALSYSTEMPLUGINSRECORD_H
