#ifndef STRINGPROCESSORMANAGER_H
#define STRINGPROCESSORMANAGER_H

#include <memory>
#include "formatter.h"
#include <QVector>

class QDataStream;

using namespace std;

class StringProcessorManager
{
public:
    StringProcessorManager();
    StringProcessorManager(const QVector<shared_ptr<StringProcessor>> &processors);
    StringProcessorManager(QDataStream &stream, const QVector<shared_ptr<StringProcessor>> &processors);

    void unserialize(QDataStream &stream, const QVector<shared_ptr<StringProcessor>> &processors);

    void addProcessor(const shared_ptr<StringProcessor> &processor);
    void removeProcessor(const unsigned int index);

    void turnOnProcessor(const unsigned int index);
    void turnOffProcessor(const unsigned int index);
    void toggleProcessor(const unsigned int index);

    QString format(const QString &input) const;

    QString toString() const;

    QVector<StringProcessor *> getProcessors();

private:
    QVector<shared_ptr<StringProcessor>> processors;
    Formatter formatter;

    friend QDataStream &operator <<(QDataStream &stream, const StringProcessorManager &manager);
};

QDataStream &operator <<(QDataStream &stream, const StringProcessorManager &manager);

#endif // STRINGPROCESSORMANAGER_H
