#ifndef LOGICALSYSTEMPLUGINSRECORD_H
#define LOGICALSYSTEMPLUGINSRECORD_H

#include <QString>

class QDataStream;

class LogicalSystemPluginsRecord
{
public:
    LogicalSystemPluginsRecord();
    LogicalSystemPluginsRecord(const QStringList &inferenceRulesNamesList, const QString &signatureName);

    QStringList getInferenceRulesNamesList() const;
    void setInferenceRulesNamesList(const QStringList &value);

    QString getSignatureName() const;
    void setSignatureName(const QString &value);

private:
    QStringList inferenceRulesNamesList;
    QString signatureName;

    friend QDataStream &operator << (QDataStream &, const LogicalSystemPluginsRecord &);
    friend QDataStream &operator >> (QDataStream &, LogicalSystemPluginsRecord &);
};

QDataStream &operator << (QDataStream &stream, const LogicalSystemPluginsRecord &pluginsRecord);
QDataStream &operator >> (QDataStream &stream, LogicalSystemPluginsRecord &pluginsRecord);

#endif // LOGICALSYSTEMPLUGINSRECORD_H
