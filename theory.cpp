#include "theory.h"
#include "logicalsystem.h"

Theory::Theory(const LogicalSystem * const parentLogic) :
    parentLogic(parentLogic)
{
}

Theory::Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, SignaturePlugin * const signaturePlugin, const QLinkedList<Formula> &axioms) :
    parentLogic(parentLogic),
    name(name),
    description(description),
    signaturePlugin(signaturePlugin),
    axioms(axioms)
{
    //Gotta do some validation! Axioms for instance, there cannot be duplicates!
    //Maybe this needs a builder...

    parser.reset(new Parser(signaturePlugin, parentLogic->getWffType()));
}

Theory::Theory(const LogicalSystem * const parentLogic, QDataStream &stream, SignaturePlugin * const signaturePlugin, const QVector<InferenceTactic *> &inferenceTactics, const QVector<StringProcessorPlugin *> &preProcessors, const QVector<StringProcessorPlugin *> &postProcessors) :
    parentLogic(parentLogic),
    signaturePlugin(signaturePlugin),
    inferenceTactics(inferenceTactics),
    preProcessors(preProcessors),
    postProcessors(postProcessors)
{
    stream >> name >> description;
    unserializePlugins(stream);
    parser.reset(new Parser(signaturePlugin, parentLogic->getWffType()));
    axioms = Formula::unserializeList(stream, signaturePlugin);
}

const LogicalSystem *Theory::getParentLogic() const
{
    return parentLogic;
}

//void Theory::setParentLogic(const LogicalSystem * const value)
//{
//    parentLogic = value;
//}

const Signature *Theory::getSignature() const
{
    return signaturePlugin;
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

QVector<InferenceTactic *> Theory::getInferenceTactics() const
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

void Theory::setInferenceTactics(const QVector<InferenceTactic *> &value)
{
    inferenceTactics = value;
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

SignaturePlugin *Theory::getSignaturePlugin()
{
    return signaturePlugin;
}

void Theory::setAxioms(const QLinkedList<Formula> &value)
{
    axioms = value;
}

void Theory::setSignaturePlugin(SignaturePlugin * const value)
{
    signaturePlugin = value;
    parser.reset(new Parser(signaturePlugin, parentLogic->getWffType()));
}

void Theory::serializePlugins(QDataStream &stream) const
{
    stream << *signaturePlugin;
    PluginManager::serializePluginVector<StringProcessorPlugin>(stream, preProcessors);
    PluginManager::serializePluginVector<StringProcessorPlugin>(stream, postProcessors);
}

void Theory::unserializePlugins(QDataStream &stream)
{
    stream >> *signaturePlugin;
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



