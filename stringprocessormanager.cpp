#include "stringprocessormanager.h"
#include "containerauxiliarytools.h"

StringProcessorManager::StringProcessorManager(const QVector<shared_ptr<StringProcessor> > &processors) :
    processors(processors)
{

}

StringProcessorManager::StringProcessorManager(QDataStream &stream, const QVector<shared_ptr<StringProcessor> > &processors) :
    processors(processors),
    formatter(stream, ContainerAuxiliaryTools::adaptFromSmartPointerContainer<QVector<shared_ptr<StringProcessor>>, QVector<StringProcessor *>>(processors))
{
}

void StringProcessorManager::deserialize(QDataStream &stream, const QVector<shared_ptr<StringProcessor> > &processors)
{
    this->processors = processors;
    formatter.deserialize(stream, ContainerAuxiliaryTools::adaptFromSmartPointerContainer<QVector<shared_ptr<StringProcessor>>, QVector<StringProcessor *>>(processors));
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

QVector<StringProcessor *> StringProcessorManager::getProcessors()
{
    return ContainerAuxiliaryTools::adaptFromSmartPointerContainer
           <QVector<shared_ptr<StringProcessor>>, QVector<StringProcessor *>>(processors);
}

QVector<const StringProcessor *> StringProcessorManager::getProcessors() const
{
    return ContainerAuxiliaryTools::adaptFromSmartPointerContainer
           <QVector<shared_ptr<StringProcessor>>, QVector<const StringProcessor *>>(processors);
}

QDataStream &operator <<(QDataStream &stream, const StringProcessorManager &manager)
{
    stream << manager.formatter;
    return stream;
}

