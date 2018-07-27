#include "theory.h"
#include "logicalsystem.h"

Theory::Theory(const LogicalSystem * const parentLogic) :
    parentLogic(parentLogic)
{

}

Theory::Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, const QLinkedList<Formula> axioms, const QString &signaturePluginName, const QStringList &inferenceTacticsPluginsNameList, const QStringList &preProcessorPluginsNameList, const QStringList &postProcessorPluginsNameList) :
    parentLogic(parentLogic),
    name(name),
    description(description),
    axioms(axioms),
    signaturePluginName(signaturePluginName),
    inferenceTacticsPluginsNameList(inferenceTacticsPluginsNameList),
    preProcessorPluginsNameList(preProcessorPluginsNameList),
    postProcessorPluginsNameList(postProcessorPluginsNameList)
{
    //Gotta do some validation! Axioms for instance, there cannot be duplicates!
    //Maybe this needs a builder...


}

const LogicalSystem *Theory::getParentLogic() const
{
    return parentLogic;
}

void Theory::setParentLogic(const LogicalSystem * const value)
{
    parentLogic = value;
}

const Signature *Theory::getSignature() const
{
    return signaturePlugin->getSignature();
}

Parser *Theory::getParser() const
{
    return parser.get();
}

QVector<const Proof *> Theory::findProofsWithConclusion(const QString &formula) const
{
    QVector<const Proof *> proofList;

    std::for_each(proofs.begin(), proofs.end(), [&formula, &proofList](const shared_ptr<Proof> &proof)
    {
        if(proof->getConclusion()->formattedString() == formula)
        {
            proofList.push_back(proof.get());
        }
    });

    return proofList;
}

QVector<const Proof *> Theory::findProofsWithPremise(const QString &formula) const
{
    QVector<const Proof *> proofList;

    std::for_each(proofs.begin(), proofs.end(), [&formula, &proofList](const shared_ptr<Proof> &proof)
    {
        const QVector<const Formula *> premises = proof->getPremises();
        bool containsPremise = std::any_of(premises.begin(), premises.end(), [&formula](const Formula * const premise)
        {
            return premise->formattedString() == formula;
        });

        if(containsPremise)
        {
            proofList.push_back(proof.get());
        }
    });

    return proofList;
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

void Theory::serializePlugins(QDataStream &stream) const
{
    stream << *signaturePlugin;
    serializePluginVector<InferenceTactic>(stream, inferenceTactics);
    serializePluginVector<StringProcessorPlugin>(stream, preProcessorPlugins);
    serializePluginVector<StringProcessorPlugin>(stream, postProcessorPlugins);
}

void Theory::unserializePlugins(QDataStream &stream)
{
    stream >> *signaturePlugin;
    unserializePluginVector<InferenceTactic>(stream, inferenceTactics);
    unserializePluginVector<StringProcessorPlugin>(stream, preProcessorPlugins);
    unserializePluginVector<StringProcessorPlugin>(stream, postProcessorPlugins);
}

void Theory::loadPlugins()
{
    //Load Signature
    QPluginLoader loader;
    loader.setFileName(StorageManager::signaturePluginPath(signaturePluginName));
}

QDataStream &operator <<(QDataStream &stream, const Theory &theory)
{
    stream << theory.name << theory.description << theory.signaturePluginName << theory.axioms << theory.inferenceTacticsPluginsNameList << theory.preProcessorPluginsNameList << theory.postProcessorPluginsNameList;

    theory.serializePlugins(stream);

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Theory &theory)
{
    stream >> theory.name >> theory.description >> theory.signaturePluginName >> theory.inferenceTacticsPluginsNameList >> theory.preProcessorPluginsNameList >> theory.postProcessorPluginsNameList;

    //Then load plugins


    //Then unserialize plugins
    theory.unserializePlugins(stream);

    theory.axioms = Formula::unserializeList(stream, theory.signaturePlugin->getSignature()); //FIXME!
    return stream;
}

QLinkedList<Formula> Theory::getAxioms() const
{
    return axioms;
}



