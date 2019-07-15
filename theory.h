#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "parser.h"
#include "signature.h"
#include "stringprocessormanager.h"

class StringProcessor;
class InferenceTactic;
class LogicalSystem;
class ProofAssistant;
class Proof;

class Theory
{
public:
    Theory(const LogicalSystem *logicalSystem,
           const shared_ptr<Signature> &signature,
           const QVector<shared_ptr<const InferenceTactic>> &inferenceTactics,
           const QVector<shared_ptr<StringProcessor>> &preProcessors,
           const QVector<shared_ptr<StringProcessor>> &postProcessors,
           QDataStream &stream);

    const LogicalSystem *getParentLogic() const;

    QString getName() const;
    QString getDescription() const;
    Signature *getSignature() const;
    QLinkedList<Formula> getAxioms() const;

    QVector<shared_ptr<const InferenceTactic>> &getInferenceTactics();
    const QVector<shared_ptr<const InferenceTactic>> &getInferenceTactics() const;
    StringProcessorManager &getPreFormatter();
    const StringProcessorManager &getPreFormatter() const;
    StringProcessorManager &getPostFormatter();
    const StringProcessorManager &getPostFormatter() const;

protected:
    Theory(const LogicalSystem * const parentLogic,
           const QString &name,
           const QString &description,
           const shared_ptr<Signature> &signature,
           const QLinkedList<Formula> &axioms);

    const LogicalSystem *parentLogic;

    QString name;
    QString description;
    unique_ptr<const Parser> parser;
    shared_ptr<Signature> signature;
    QLinkedList<Formula> axioms; //Linked list because there will be pointers pointing to axioms! NOTE Will there?

    QVector<shared_ptr<const InferenceTactic>> inferenceTactics;

    StringProcessorManager preFormatter;
    StringProcessorManager postFormatter;

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
QDataStream &operator <<(QDataStream &stream, const QVector<shared_ptr<StringProcessor>> &processors);
QDataStream &operator >>(QDataStream &stream, QVector<shared_ptr<StringProcessor>> &processors);

#endif // THEORY_H
