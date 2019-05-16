#include "theorybuilder.h"
#include "logicalsystem.h"
#include "parser.h"
#include "parsingtree.h"
#include "storagemanager.h"

TheoryBuilder::TheoryBuilder(const LogicalSystem *parentLogic)
{
    checkParentLogicPointer(parentLogic);
    this->parentLogic = parentLogic;
    loadSignaturePlugin();
}

TheoryBuilder::TheoryBuilder(const LogicalSystem *parentLogic, const QString &name, const QString &description) :
    name(name),
    description(description)
{
    checkParentLogicPointer(parentLogic);
    this->parentLogic = parentLogic;
    loadSignaturePlugin();
}

Theory TheoryBuilder::build() const
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

void TheoryBuilder::checkAxiomCollision(const Formula &newAxiom) const
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

void TheoryBuilder::checkParentLogicPointer(const LogicalSystem *parentLogic) const
{
    if(parentLogic == nullptr)
    {
        throw std::runtime_error("Parent logic pointer is null!");
    }
}

void TheoryBuilder::loadSignaturePlugin()
{
    signaturePlugin.load(StorageManager::signaturePluginPath(parentLogic->getSignatureName()));
    parser.reset(new Parser(getSignature(), parentLogic->getWffType()));
}

void TheoryBuilder::setName(const QString &value)
{
    name = value;
}

void TheoryBuilder::setDescription(const QString &value)
{
    description = value;
}
