#ifndef LOGICALSYSTEMPLUGINSRECORD_H
#define LOGICALSYSTEMPLUGINSRECORD_H

#include <QString>
#include <QStringList>

class QDataStream;

struct LogicalSystemPluginsRecord
{
public:
    LogicalSystemPluginsRecord();
    LogicalSystemPluginsRecord(const QStringList &inferenceRulesNamesList, const QString &signatureName, const QString &proofName);

    const QStringList &getInferenceRulesNamesList() const;
    const QString &getSignatureName() const;
    const QString &getProofName() const;

    QStringList inferenceRulesNamesList;
    QString signatureName;
    QString proofName;

    friend QDataStream &operator << (QDataStream &, const LogicalSystemPluginsRecord &);
    friend QDataStream &operator >> (QDataStream &, LogicalSystemPluginsRecord &);
};

QDataStream &operator << (QDataStream &stream, const LogicalSystemPluginsRecord &pluginsRecord);
QDataStream &operator >> (QDataStream &stream, LogicalSystemPluginsRecord &pluginsRecord);

#endif // LOGICALSYSTEMPLUGINSRECORD_H
