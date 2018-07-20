#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "proof.h"
#include "parser.h"
#include "inferencetactic.h"
#include "stringprocessor.h"
#include "formatter.h"
#include <QDataStream>

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

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

private:
    QString name;
    QString description;
    unique_ptr<Signature> signature;
    unique_ptr<Parser> parser;
    QLinkedList<Formula> axioms; //Linked list because there will be pointers pointing to axioms!
    QVector<shared_ptr<Proof>> proofs; //Maybe using a vector will be KEY to serialize/unserialize proof links! Think this through! TODO
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
    friend QDataStream &operator <<(QDataStream &stream, const Theory &theory);
    friend QDataStream &operator >>(QDataStream &stream, Theory &theory);
};

QDataStream &operator <<(QDataStream &stream, const Theory &theory);
QDataStream &operator >>(QDataStream &stream, Theory &theory);

#endif // THEORY_H
