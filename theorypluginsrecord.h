#ifndef THEORYPLUGINSRECORD_H
#define THEORYPLUGINSRECORD_H

#include <QString>
#include <QStringList>

class QDataStream;

struct TheoryPluginsRecord
{
    TheoryPluginsRecord();
    TheoryPluginsRecord(const QString &signaturePluginName,
                        const QStringList &inferenceTacticsPluginsNameList = QStringList(),
                        const QStringList &preProcessorsPluginsNameList = QStringList(),
                        const QStringList &postProcessorsPluginsNameList = QStringList());

    QString signaturePluginName;
    QStringList inferenceTacticsPluginsNameList;
    QStringList preProcessorsPluginsNameList;
    QStringList postProcessorsPluginsNameList;
};

QDataStream &operator <<(QDataStream &stream, const TheoryPluginsRecord &record);
QDataStream &operator >>(QDataStream &stream, TheoryPluginsRecord &record);

#endif // THEORYPLUGINSRECORD_H

