#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "proof.h"
#include "parser.h"

class LogicalSystem;

class Theory
{
public:
    Theory();
    Theory(const LogicalSystem * const parentLogic);

    void addAxiom(const QString &axiom);
    void removeAxiom(const QString &axiom);
    QVector<Formula> getAxioms() const;

    const LogicalSystem *getParentLogic() const;
    void setParentLogic(const LogicalSystem * const value);

    Signature *getSignature() const;
    void setSignature(Signature * const signature);

    Parser *getParser() const;

    QLinkedList<Proof> getProofs() const;

    QVector<const Proof *> findProofsWithConclusion(const QString &formula) const;
    QVector<const Proof *> findProofsWithPremiss(const QString &formula) const;

private:
    QString name;
    unique_ptr<Parser> parser;
    unique_ptr<Signature> signature;
    QVector<Formula> axioms;
    QLinkedList<Proof> proofs; //NOTE Why linked list?
    const LogicalSystem *parentLogic;
};

#endif // THEORY_H
