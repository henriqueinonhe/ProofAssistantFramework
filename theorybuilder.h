#ifndef THEORYBUILDER_H
#define THEORYBUILDER_H

#include "theory.h"

class TheoryBuilder
{
public:
    TheoryBuilder(const LogicalSystem *parentLogic,
                  const QString &name,
                  const QString &description,
                  const shared_ptr<Signature> &signature);
    TheoryBuilder(const LogicalSystem *parentLogic,
                  const shared_ptr<Signature> &signature);

    Theory build() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    shared_ptr<Signature> getSignature();

    void addAxiom(const QString &axiom);
    void removeAxiom(const QString &axiom);

    QLinkedList<Formula> getAxioms() const;

protected:
    void loadSignature(const QString &signatureName);

    const LogicalSystem *parentLogic;
    QString name;
    QString description;
    shared_ptr<Signature> signature;
    unique_ptr<const Parser> parser;
    QLinkedList<Formula> axioms;

private:
    void checkParentLogicPointer(const LogicalSystem *parentLogic) const;
    void checkAxiomCollision(const Formula &newAxiom) const;
};

#endif // THEORYBUILDER_H
