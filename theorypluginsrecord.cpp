#include "theorypluginsrecord.h"
#include <QDataStream>

TheoryPluginsRecord::TheoryPluginsRecord()
{

}

TheoryPluginsRecord::TheoryPluginsRecord(const QString &signaturePluginName, const QStringList &inferenceTacticsPluginsNameList, const QStringList &preProcessorsPluginsNameList, const QStringList &postProcessorsPluginsNameList) :
    signaturePluginName(signaturePluginName),
    inferenceTacticsPluginsNameList(inferenceTacticsPluginsNameList),
    preProcessorsPluginsNameList(preProcessorsPluginsNameList),
    postProcessorsPluginsNameList(postProcessorsPluginsNameList)
{
}

QDataStream &operator <<(QDataStream &stream, const TheoryPluginsRecord &record)
{
    stream << record.signaturePluginName
           << record.inferenceTacticsPluginsNameList
           << record.preProcessorsPluginsNameList
           << record.postProcessorsPluginsNameList;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TheoryPluginsRecord &record)
{
    stream >> record.signaturePluginName
           >> record.inferenceTacticsPluginsNameList
           >> record.preProcessorsPluginsNameList
           >> record.postProcessorsPluginsNameList;
    return stream;
}
