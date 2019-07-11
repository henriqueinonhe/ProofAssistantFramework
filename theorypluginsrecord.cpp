#include "theorypluginsrecord.h"
#include <QDataStream>

TheoryPluginsRecord::TheoryPluginsRecord(const QStringList &inferenceTacticsPluginsNameList, const QStringList &preProcessorsPluginsNameList, const QStringList &postProcessorsPluginsNameList) :
    inferenceTacticsPluginsNameList(inferenceTacticsPluginsNameList),
    preProcessorsPluginsNameList(preProcessorsPluginsNameList),
    postProcessorsPluginsNameList(postProcessorsPluginsNameList)
{
}

QDataStream &operator <<(QDataStream &stream, const TheoryPluginsRecord &record)
{
    stream << record.inferenceTacticsPluginsNameList
           << record.preProcessorsPluginsNameList
           << record.postProcessorsPluginsNameList;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TheoryPluginsRecord &record)
{
    stream >> record.inferenceTacticsPluginsNameList
           >> record.preProcessorsPluginsNameList
           >> record.postProcessorsPluginsNameList;
    return stream;
}
