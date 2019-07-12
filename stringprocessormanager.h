#ifndef STRINGPROCESSORMANAGER_H
#define STRINGPROCESSORMANAGER_H

#include "formatter.h"
#include <QVector>

class QDataStream;

class StringProcessorManager
{
public:
    StringProcessorManager();
    StringProcessorManager(QDataStream &stream, const QVector<StringProcessor *> &processorList);

    void addProcessor(const QVector<StringProcessor *> &processorList, const unsigned int processorIndex);
    void removeProcessor(const unsigned int processorIndex);
    void moveProcessor(const unsigned int locationIndex, const unsigned int targetIndex);

    void turnOnProcessor(const unsigned int processorIndex);
    void turnOffProcessor(const unsigned int processorIndex);
    void toggleProcessor(const unsigned int processorIndex);

    QString format(const QString &input);

private:
    Formatter formatter;
    QVector<unsigned int> processorsIndexList;

    friend QDataStream &operator <<(QDataStream &stream, const StringProcessorManager &manager);
};

QDataStream &operator <<(QDataStream &stream, const StringProcessorManager &manager);

#endif // STRINGPROCESSORMANAGER_H
