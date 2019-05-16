#include "theory.h"
#include "logicalsystem.h"
#include "storagemanager.h"
#include <QDataStream>

Theory::Theory(const LogicalSystem * const parentLogic) :
    parentLogic(parentLogic)
{
}

void Theory::loadSignaturePlugin()
{
    const QString signatureName = parentLogic->getSignatureName();
    const QString signaturePluginPath = StorageManager::signaturePluginPath(signatureName);
    signaturePlugin.load(signaturePluginPath);
}

QVector<StringProcessorPluginWrapper> Theory::getPostProcessors() const
{
    return postProcessors;
}

QVector<StringProcessorPluginWrapper> Theory::getPreProcessors() const
{
    return preProcessors;
}

void Theory::addPostProcessor(const QString &pluginName)
{
    const QString pluginPath = StorageManager::postProcessorPluginPath(pluginName);
    PluginWrapper<StringProcessorPlugin>::addPluginInContainer(postProcessors, pluginPath);
}

void Theory::removePostProcessor(const QString &pluginName)
{
    const QString pluginPath = StorageManager::postProcessorPluginPath(pluginName);
    PluginWrapper<StringProcessorPlugin>::removePluginFromContainer(postProcessors, pluginPath);
}

Theory::Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, const QLinkedList<Formula> &axioms) :
    parentLogic(parentLogic),
    name(name),
    description(description),
    axioms(axioms)
{
    loadSignaturePlugin();
    parser.reset(new Parser(getSignature(), parentLogic->getWffType()));
}

Theory::Theory(const LogicalSystem *parentLogic, QDataStream &stream) :
    parentLogic(parentLogic)
{
    stream >> *this;
}

const LogicalSystem *Theory::getParentLogic() const
{
    return parentLogic;
}

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

QVector<InferenceTacticPluginWrapper> Theory::getInferenceTactics() const
{
    return inferenceTactics;
}

void Theory::addPreProcessor(const QString &pluginName)
{
    const QString pluginPath = StorageManager::preProcessorPluginPath(pluginName);
    PluginWrapper<StringProcessorPlugin>::addPluginInContainer(preProcessors, pluginPath);
}

void Theory::removePreProcessor(const QString &pluginName)
{
    const QString pluginPath = StorageManager::preProcessorPluginPath(pluginName);
    PluginWrapper<StringProcessorPlugin>::removePluginFromContainer(preProcessors, pluginPath);
}

QString Theory::getName() const
{
    return name;
}

QString Theory::getDescription() const
{
    return description;
}

QDataStream &operator <<(QDataStream &stream, const Theory &theory)
{
    stream << theory.name
           << theory.description
           << theory.signaturePlugin
           << theory.axioms
           << theory.inferenceTactics
           << theory.preProcessors
           << theory.postProcessors
           << theory.preFormatter
           << theory.postFormatter;

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Theory &theory)
{
    stream >> theory.name
           >> theory.description
           >> theory.signaturePlugin;
    theory.axioms = Formula::unserializeList(stream, theory.signaturePlugin.ptr());
    stream >> theory.inferenceTactics
           >> theory.preProcessors
           >> theory.postProcessors
           >> theory.preFormatter
           >> theory.postFormatter;

    return stream;
}

QLinkedList<Formula> Theory::getAxioms() const
{
    return axioms;
}

void Theory::addInferenceTactic(const QString &pluginName)
{
    const QString pluginPath = StorageManager::inferenceTacticPluginPath(pluginName);
    PluginWrapper<InferenceTactic>::addPluginInContainer(inferenceTactics, pluginPath);
}

void Theory::removeInferenceTactic(const QString &pluginName)
{
    const QString pluginPath = StorageManager::inferenceTacticPluginPath(pluginName);
    PluginWrapper<InferenceTactic>::removePluginFromContainer(inferenceTactics, pluginPath);
}



