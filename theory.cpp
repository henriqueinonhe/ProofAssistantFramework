#include "theory.h"
#include "logicalsystem.h"
#include "pluginmanager.h"

Theory::Theory(const LogicalSystem * const parentLogic) :
    parentLogic(parentLogic)
{
}

void Theory::loadSignaturePlugin()
{
    const QString signaturePluginPath = StorageManager::signaturePluginPath(parentLogic->getSignatureName());
    signaturePlugin.load(signaturePluginPath);
}

Theory::Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, const QLinkedList<Formula> &axioms) :
    parentLogic(parentLogic),
    name(name),
    description(description),
    axioms(axioms)
{
    //Gotta do some validation! Axioms for instance, there cannot be duplicates!
    //Maybe this needs a builder...

    loadSignaturePlugin();
    parser.reset(new Parser(getSignature(), parentLogic->getWffType()));

}

Theory::Theory(const LogicalSystem * const parentLogic, QDataStream &stream) :
    parentLogic(parentLogic)
{
    stream >> name >> description;
    unserializePlugins(stream);
    parser.reset(new Parser(getSignature(), parentLogic->getWffType()));
    axioms = Formula::unserializeList(stream, getSignature());
}

const LogicalSystem *Theory::getParentLogic() const
{
    return parentLogic;
}

//void Theory::setParentLogic(const LogicalSystem * const value)
//{
//    parentLogic = value;
//}

Signature *Theory::getSignature()
{
    return signaturePlugin.ptr();
}

QVector<const Proof *> Theory::findProofsWithConclusion(const QString &formula) const
{
//    QVector<const Proof *> proofList;

//    std::for_each(proofs.begin(), proofs.end(), [&formula, &proofList](const shared_ptr<Proof> &proof)
//    {
//        if(proof->getConclusion()->formattedString() == formula)
//        {
//            proofList.push_back(proof.get());
//        }
//    });

//    return proofList;
    //FIXME
}

QVector<const Proof *> Theory::findProofsWithPremise(const QString &formula) const
{
//    QVector<const Proof *> proofList;

//    std::for_each(proofs.begin(), proofs.end(), [&formula, &proofList](const shared_ptr<Proof> &proof)
//    {
//        const QVector<const Formula *> premises = proof->getPremises();
//        bool containsPremise = std::any_of(premises.begin(), premises.end(), [&formula](const Formula * const premise)
//        {
//            return premise->formattedString() == formula;
//        });

//        if(containsPremise)
//        {
//            proofList.push_back(proof.get());
//        }
//    });

//    return proofList;
    //FIXME
}

QVector<InferenceTacticPlugin> Theory::getInferenceTactics() const
{
    return inferenceTactics;
}

QString Theory::getName() const
{
    return name;
}

void Theory::setName(const QString &value)
{
    name = value;
}

QString Theory::getDescription() const
{
    return description;
}

void Theory::setDescription(const QString &value)
{
    description = value;
}

QVector<StringProcessorPlugin *> Theory::getPreProcessors() const
{
    return preProcessors;
}

void Theory::setPreProcessors(const QVector<StringProcessorPlugin *> &value)
{
    preProcessors = value;
}

QVector<StringProcessorPlugin *> Theory::getPostProcessors() const
{
    return postProcessors;
}

void Theory::setPostProcessors(const QVector<StringProcessorPlugin *> &value)
{
    postProcessors = value;
}

void Theory::setAxioms(const QLinkedList<Formula> &value)
{
    axioms = value;
}

void Theory::serializePlugins(QDataStream &stream) const
{
    //stream << signaturePlugin->ptr();
    PluginManager::serializePluginVector<StringProcessorPlugin>(stream, preProcessors);
    PluginManager::serializePluginVector<StringProcessorPlugin>(stream, postProcessors);
}

void Theory::unserializePlugins(QDataStream &stream)
{
    //stream >> signaturePlugin->ptr();
    PluginManager::unserializePluginVector<StringProcessorPlugin>(stream, preProcessors);
    PluginManager::unserializePluginVector<StringProcessorPlugin>(stream, postProcessors);
}

//void Theory::loadPlugins()
//{
//    //Load Signature
//    PluginManager::loadSinglePlugin<SignaturePlugin>(signaturePlugin, signaturePluginName, StorageManager::signaturePluginPath);

//    //Load Inference Tactics
//    PluginManager::loadPluginVector<InferenceTactic>(inferenceTactics,
//                                                     inferenceTacticsPluginsNameList,
//                                                     StorageManager::inferenceTacticPluginPath);

//    //Load Pre Processors
//    PluginManager::loadPluginVector<StringProcessorPlugin>(preProcessorPlugins,
//                                                           preProcessorPluginsNameList,
//                                                           StorageManager::preProcessorPluginPath);

//    //Load Post Processors
//    PluginManager::loadPluginVector<StringProcessorPlugin>(postProcessorPlugins,
//                                                           postProcessorPluginsNameList,
//                                                           StorageManager::postProcessorPluginPath);
//}

QDataStream &operator <<(QDataStream &stream, const Theory &theory)
{
    stream << theory.name << theory.description;
    theory.serializePlugins(stream);
    stream << theory.axioms;

    return stream;
}

//QDataStream &operator >>(QDataStream &stream, Theory &theory)
//{
//    stream >> theory.name >> theory.description;

//    return stream;
//}

QLinkedList<Formula> Theory::getAxioms() const
{
    return axioms;
}



