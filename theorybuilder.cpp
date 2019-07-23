#include "theorybuilder.h"
#include "logicalsystem.h"
#include "parser.h"
#include "parsingtree.h"
#include "storagemanager.h"
#include "pluginmanager.h"

TheoryBuilder::TheoryBuilder(const LogicalSystem *parentLogic, const shared_ptr<Signature> &signature, const QString &name, const QString &description) :
    parentLogic(checkParentLogicPointer(parentLogic)),
    signature(signature),
    name(name),
    description(description),
    parser(new Parser(signature.get(), parentLogic->getWffType()))
{
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

shared_ptr<Signature> TheoryBuilder::getSignature()
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

        throw std::invalid_argument(errorMsg.toStdString());
    }
}

void TheoryBuilder::addAxiom(const QString &axiom)
{
    auto newAxiom = parser->parse(axiom);
    checkAxiomCollision(newAxiom);

    axioms.push_back(newAxiom);
}

void TheoryBuilder::removeAxiom(const QString &axiom)
{
    for(const auto &axiomFormula : axioms)
    {
        if(axiomFormula.formattedString() == axiom)
        {
            axioms.removeAll(axiomFormula);
            return;
        }
    }

    QString errorMsg;
    errorMsg += "Axiom list doesn't contain \"";
    errorMsg += axiom;
    errorMsg += "\".";
    throw invalid_argument(errorMsg.toStdString());
}

void TheoryBuilder::removeAxiom(const unsigned int index)
{
    if(index >= static_cast<uint>(axioms.size()))
    {
        throw invalid_argument("There is no axiom associated with this index!");
    }

    auto iter = axioms.begin();
    iter += index;
    axioms.removeOne(*iter);
}

void TheoryBuilder::loadSignature(const QString &signatureName)
{
    signature = PluginManager::fetchPlugin<Signature>(StorageManager::signaturePluginPath(signatureName));
}

QLinkedList<Formula> TheoryBuilder::getAxioms() const
{
    return axioms;
}

const LogicalSystem *TheoryBuilder::checkParentLogicPointer(const LogicalSystem *parentLogic) const
{
    if(parentLogic == nullptr)
    {
        throw std::runtime_error("Parent logic pointer is null!");
    }
    return parentLogic;
}

void TheoryBuilder::setName(const QString &value)
{
    name = value;
}

void TheoryBuilder::setDescription(const QString &value)
{
    description = value;
}
