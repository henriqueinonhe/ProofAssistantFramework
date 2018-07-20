#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "proof.h"
#include "parser.h"
#include "inferencetactic.h"
#include "stringprocessor.h"
#include "formatter.h"

class LogicalSystem;
class ProofAssistant;

class Theory
{
public:
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
    QString description;
    unique_ptr<Parser> parser;
    unique_ptr<Signature> signature;
    QLinkedList<Formula> axioms; //NOTE Do we really need a linked list here? Maybe use axiom entries to also describe/comment them? Or is that too much?
    QVector<shared_ptr<Proof>> proofs;
    QVector<InferenceTactic *> inferenceTactics; //I'm using raw pointers here because QPluginLoader already deletes
                                                 //the plugin object when application terminates
    QStringList inferenceTacticsPluginsNameList;
    QStringList postProcessorPluginsNameList;
    QStringList preProcessorPluginsNameList;
    QVector<StringProcessor *> preProcessors;
    QVector<StringProcessor *> postProcessors;
    Formatter preFormatter;
    Formatter postFormatter;
    const LogicalSystem *parentLogic;

    friend class ProofAssistant;
};

#endif // THEORY_H
