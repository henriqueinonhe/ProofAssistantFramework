#include "stringprocessormanager.h"
#include "containerauxiliarytools.h"

StringProcessorManager::StringProcessorManager()
{

}

StringProcessorManager::StringProcessorManager(const QVector<shared_ptr<StringProcessor> > &processors) :
    processors(processors)
{

}

StringProcessorManager::StringProcessorManager(QDataStream &stream, const QVector<shared_ptr<StringProcessor> > &processors)
{
    unserialize(stream, processors);
}

void StringProcessorManager::unserialize(QDataStream &stream, const QVector<shared_ptr<StringProcessor> > &processors)
{
    QVector<StringProcessor *> processorsPtrs;
    ContainerAuxiliaryTools::adatpFromSmartPointerContainer(processors, processorsPtrs);

    this->processors = processors;
    formatter.unserialize(stream, processorsPtrs);
}

void StringProcessorManager::addProcessor(const shared_ptr<StringProcessor> &processor)
{
    processors.push_back(processor);
    formatter.addProcessor(processor.get());
}

void StringProcessorManager::removeProcessor(const unsigned int index)
{
    processors.remove(index);
    formatter.removeProcessor(index);
}

void StringProcessorManager::turnOnProcessor(const unsigned int index)
{
    formatter.turnOnProcessor(index);
}

void StringProcessorManager::turnOffProcessor(const unsigned int index)
{
    formatter.turnOffProcessor(index);
}

void StringProcessorManager::toggleProcessor(const unsigned int index)
{
    formatter.toggleProcessor(index);
}

QString StringProcessorManager::format(const QString &input) const
{
    return formatter.format(input);
}

QString StringProcessorManager::toString() const
{
    return formatter.toString();
}

QDataStream &operator <<(QDataStream &stream, const StringProcessorManager &manager)
{
    stream << manager.formatter;
    return stream;
}
