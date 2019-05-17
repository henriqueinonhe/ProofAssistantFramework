#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "formatter.h"
#include "parser.h"
#include "signature.h"

class StringProcessor;
class InferenceTactic;
class LogicalSystem;
class ProofAssistant;
class Proof;

class Theory
{
public:
    Theory(const LogicalSystem *logicalSystem, shared_ptr<Signature> signature, QDataStream &stream);

    const LogicalSystem *getParentLogic() const;

    QString getName() const;
    QString getDescription() const;
    Signature *getSignature();
    QLinkedList<Formula> getAxioms() const;

    QVector<shared_ptr<const InferenceTactic>> &getInferenceTactics();

    QVector<shared_ptr<StringProcessor>> &getPreProcessors();

    QVector<shared_ptr<StringProcessor>> &getPostProcessors();

    QVector<const Proof *> findProofsWithConclusion(const QString &formula) const;
    QVector<const Proof *> findProofsWithPremise(const QString &formula) const;

protected:
    Theory(const LogicalSystem * const parentLogic);
    Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, Signature *signature, const QLinkedList<Formula> &axioms);

    void serializePlugins() const;

    const LogicalSystem *parentLogic;

    QString name;
    QString description;
    unique_ptr<Parser> parser;
    shared_ptr<Signature> signature;
    QLinkedList<Formula> axioms; //Linked list because there will be pointers pointing to axioms!

    QVector<shared_ptr<const InferenceTactic>> inferenceTactics;
    QVector<shared_ptr<StringProcessor>> preProcessors;
    QVector<shared_ptr<StringProcessor>> postProcessors;
    Formatter preFormatter;
    Formatter postFormatter;

    friend class ProofAssistant;
    friend class TheoryBuilder;
    friend class ProgramManager;
    friend QDataStream &operator <<(QDataStream &stream, const Theory &theory);
    friend QDataStream &operator >>(QDataStream &stream, Theory &theory);
};

QDataStream &operator <<(QDataStream &stream, const Theory &theory);
QDataStream &operator >>(QDataStream &stream, Theory &theory);
QDataStream &operator <<(QDataStream &stream, const shared_ptr<Signature> &signature);
QDataStream &operator >>(QDataStream &stream,  shared_ptr<Signature> &signature);
QDataStream &operator <<(QDataStream &stream, const shared_ptr<StringProcessor> &processor);
QDataStream &operator >>(QDataStream &stream, shared_ptr<StringProcessor> &processor);

#endif // THEORY_H
