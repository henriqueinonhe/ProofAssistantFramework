#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "proof.h"
#include "parser.h"
#include "inferencetactic.h"

class LogicalSystem;

class Theory
{
public:
    Theory();
    Theory(const LogicalSystem * const parentLogic);

    void addAxiom(const QString &axiom);
    void removeAxiom(const QString &axiom);
    QLinkedList<Formula> getAxioms() const;

    const LogicalSystem *getParentLogic() const;
    void setParentLogic(const LogicalSystem * const value);

    Signature *getSignature() const;
    void setSignature(Signature * const signature);

    Parser *getParser() const;

    QLinkedList<Proof> getProofs() const;

    QVector<const Proof *> findProofsWithConclusion(const QString &formula) const;
    QVector<const Proof *> findProofsWithPremise(const QString &formula) const;

    QVector<InferenceTactic *> getInferenceTactics() const;

private:
    QString name;
    unique_ptr<Parser> parser;
    unique_ptr<Signature> signature;
    QLinkedList<Formula> axioms; //NOTE Do we really need a linked list here?
    QLinkedList<Proof> proofs; //Linked list because proofs will be referenced by pointers
    const LogicalSystem *parentLogic;
    QVector<InferenceTactic *> inferenceTactics; //I'm using raw pointers here because QPluginLoader already deletes
                                                 //the plugin object when application terminates
};

#endif // THEORY_H
