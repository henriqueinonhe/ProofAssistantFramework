#include "stringprocessormanager.h"

#include <QDataStream>

StringProcessorManager::StringProcessorManager()
{

}

StringProcessorManager::StringProcessorManager(QDataStream &stream, const QVector<StringProcessor *> &processorList)
{
    stream >> processorsIndexList;
    QVector<StringProcessor *> actualProcessorList;
    for(const auto index : processorsIndexList)
    {
        actualProcessorList.push_back(processorList[index]);
    }
    formatter.unserialize(stream, actualProcessorList);
}

void StringProcessorManager::addProcessor(const QVector<StringProcessor *> &processorList, const unsigned int processorListIndex)
{
    if(processorListIndex >= static_cast<uint>(processorList.size()))
    {
        throw invalid_argument("There is no processor associated with this index!");
    }

    formatter.addProcessor(processorList[processorListIndex]);
    processorsIndexList.push_back(processorListIndex);
}

void StringProcessorManager::removeProcessor(const unsigned int processorIndex)
{
    formatter.removeProcessor(processorIndex);
    processorsIndexList.remove(processorIndex);
}

void StringProcessorManager::moveProcessor(const unsigned int locationIndex, const unsigned int targetIndex)
{
    //FIXME
    formatter.moveProcessor(locationIndex, targetIndex);

    const unsigned int tempLocationIndex = processorsIndexList[locationIndex];
    processorsIndexList.remove(locationIndex);
    processorsIndexList.insert(targetIndex, tempLocationIndex);
}

void StringProcessorManager::turnOnProcessor(const unsigned int processorIndex)
{
    formatter.turnOnProcessor(processorIndex);
}

void StringProcessorManager::turnOffProcessor(const unsigned int processorIndex)
{
    formatter.turnOffProcessor(processorIndex);
}

void StringProcessorManager::toggleProcessor(const unsigned int processorIndex)
{
    formatter.toggleProcessor(processorIndex);
}

QString StringProcessorManager::format(const QString &input)
{
    return formatter.format(input);
}

QDataStream &operator <<(QDataStream &stream, const StringProcessorManager &manager)
{
    stream << manager.processorsIndexList
           << manager.formatter;
    return stream;
}
