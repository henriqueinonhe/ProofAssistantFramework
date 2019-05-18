#ifndef THEORYBUILDER_H
#define THEORYBUILDER_H

#include "theory.h"

class TheoryBuilder
{
public:
    TheoryBuilder(const LogicalSystem *parentLogic,
                  const QString &name,
                  const QString &description,
                  const shared_ptr<Signature> &signature); //NOTE Maybe should decouple this from plugins
    TheoryBuilder(const LogicalSystem *parentLogic,
                  const QString &name,
                  const QString &description,
                  const QString &signatureName);
    TheoryBuilder(const LogicalSystem *parentLogic,
                  const QString &signatureName);

    Theory build() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    shared_ptr<Signature> getSignature();

    void addAxiom(const QString &axiom);
    void removeAxiom(const QString &axiom);

    QString getSignatureName() const;

protected:
    void loadSignature(const QString &signatureName);

    const LogicalSystem *parentLogic;
    QString name;
    QString description;
    QString signatureName;
    shared_ptr<Signature> signature;
    unique_ptr<Parser> parser;
    QLinkedList<Formula> axioms;

private:
    void checkParentLogicPointer(const LogicalSystem *parentLogic) const;
    void checkAxiomCollision(const Formula &newAxiom) const;
};

#endif // THEORYBUILDER_H
