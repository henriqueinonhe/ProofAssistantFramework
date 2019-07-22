#ifndef THEORYBUILDER_H
#define THEORYBUILDER_H

#include "theory.h"

class TheoryBuilder
{
public:
    TheoryBuilder() = delete;
    TheoryBuilder(const TheoryBuilder &) = delete;
    TheoryBuilder(TheoryBuilder &&) noexcept = default;
    TheoryBuilder &operator =(const TheoryBuilder &) = delete;
    TheoryBuilder &operator =(TheoryBuilder &&) = delete;
    ~TheoryBuilder() noexcept = default;

    TheoryBuilder(const LogicalSystem *parentLogic,
                  const shared_ptr<Signature> &signature,
                  const QString &name = "",
                  const QString &description = "");

    Theory build() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    shared_ptr<Signature> getSignature();

    void addAxiom(const QString &axiom);
    void removeAxiom(const QString &axiom);
    void removeAxiom(const unsigned int index);

    QLinkedList<Formula> getAxioms() const;

protected:
    void loadSignature(const QString &signatureName);

    const LogicalSystem *parentLogic;
    shared_ptr<Signature> signature;
    QString name;
    QString description;
    unique_ptr<const Parser> parser;
    QLinkedList<Formula> axioms;

private:
    const LogicalSystem *checkParentLogicPointer(const LogicalSystem *parentLogic) const;
    void checkAxiomCollision(const Formula &newAxiom) const;
};

#endif // THEORYBUILDER_H
