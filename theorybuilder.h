#ifndef THEORYBUILDER_H
#define THEORYBUILDER_H

#include "theory.h"

class TheoryBuilder
{
public:
    TheoryBuilder(const LogicalSystem *parentLogic);
    TheoryBuilder(const LogicalSystem *parentLogic,
                  const QString &name,
                  const QString &description, Signature *signature);

    Theory build() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    Signature *getSignature();

    void addAxiom(const QString &axiom);
    void removeAxiom(const QString &axiom);

protected:
    const LogicalSystem *parentLogic;
    QString name;
    QString description;
    Signature *signature;
    unique_ptr<Parser> parser;
    QLinkedList<Formula> axioms;

private:
    void checkParentLogicPointer(const LogicalSystem *parentLogic) const;
    void checkAxiomCollision(const Formula &newAxiom) const;
};

#endif // THEORYBUILDER_H
