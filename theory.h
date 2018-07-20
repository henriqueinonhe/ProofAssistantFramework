#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "proof.h"
#include "parser.h"
#include "inferencetactic.h"
#include "formatter.h"

class LogicalSystem;
class ProofAssistant;

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

    QVector<const Proof *> findProofsWithConclusion(const QString &formula) const;
    QVector<const Proof *> findProofsWithPremise(const QString &formula) const;

    QVector<InferenceTactic *> getInferenceTactics() const;

private:
    QString name;
    unique_ptr<Parser> parser;
    unique_ptr<Signature> signature;
    QLinkedList<Formula> axioms; //NOTE Do we really need a linked list here?
    QVector<shared_ptr<Proof>> proofs;
    const LogicalSystem *parentLogic;
    QVector<InferenceTactic *> inferenceTactics; //I'm using raw pointers here because QPluginLoader already deletes
                                                 //the plugin object when application terminates
    Formatter preFormatter;
    Formatter postFormatter;

    friend class ProofAssistant;
};

#endif // THEORY_H
