#include "theorybuilder.h"

TheoryBuilder::TheoryBuilder(LogicalSystem *parentLogic, const QString &name, const QString &description) :
    parentLogic(parentLogic),
    name(name),
    description(description)
{
    signaturePlugin.load(StorageManager::signaturePluginPath(parentLogic->getSignatureName()));
    parser.reset(new Parser(getSignature(), parentLogic->getWffType()));
}

Theory TheoryBuilder::build()
{
    return Theory(parentLogic, name, description, axioms);
}

QString TheoryBuilder::getName() const
{
    return name;
}

QString TheoryBuilder::getDescription() const
{
    return description;
}

Signature *TheoryBuilder::getSignature()
{
    return signaturePlugin.ptr();
}

void TheoryBuilder::checkAxiomCollision(const Formula &newAxiom)
{
    if(axioms.contains(newAxiom))
    {
        QString errorMsg;
        errorMsg += "The axiom '";
        errorMsg += newAxiom.formattedString();
        errorMsg += "' already exists.";

        throw std::runtime_error(errorMsg.toStdString());
    }
}

void TheoryBuilder::addAxiom(const QString &axiom)
{
    Formula newAxiom(parser->parse(axiom));

    checkAxiomCollision(newAxiom);

    axioms.push_back(newAxiom);
}

void TheoryBuilder::removeAxiom(const QString &axiom)
{
    //TODO
}
