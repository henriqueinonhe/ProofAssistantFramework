#include "theorybuilder.h"
#include "logicalsystem.h"
#include "parser.h"
#include "parsingtree.h"
#include "storagemanager.h"

TheoryBuilder::TheoryBuilder(const LogicalSystem *parentLogic)
{
    checkParentLogicPointer(parentLogic);
    this->parentLogic = parentLogic;
}

TheoryBuilder::TheoryBuilder(const LogicalSystem *parentLogic, const QString &name, const QString &description, Signature *signature) :
    name(name),
    description(description),
    signature(signature)
{
    checkParentLogicPointer(parentLogic);
    this->parentLogic = parentLogic;
}

Theory TheoryBuilder::build() const
{
    return Theory(parentLogic, name, description, signature, axioms);
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
    return signature;
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

void TheoryBuilder::setName(const QString &value)
{
    name = value;
}

void TheoryBuilder::setDescription(const QString &value)
{
    description = value;
}
