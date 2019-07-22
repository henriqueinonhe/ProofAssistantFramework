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
    Theory() = delete;
    Theory(const Theory &) = delete;
    Theory(Theory &&) noexcept = default;
    Theory &operator =(const Theory &) = delete;
    Theory &operator =(Theory &&) noexcept = delete;
    ~Theory() noexcept = default;

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
    const StringProcessorManager &getPreFormatter() const;
    const StringProcessorManager &getPostFormatter() const;
    StringProcessorManager &getPreFormatter();
    StringProcessorManager &getPostFormatter();

protected:
    Theory(const LogicalSystem * const parentLogic,
           const QString &name,
           const QString &description,
           const shared_ptr<Signature> &signature,
           const QLinkedList<Formula> &axioms);

    const LogicalSystem *parentLogic;

    QString name;
    QString description;
    shared_ptr<Signature> signature;
    unique_ptr<const Parser> parser;
    QLinkedList<Formula> axioms; //Linked list because there will be pointers pointing to axioms! NOTE Will there?

    QVector<shared_ptr<const InferenceTactic>> inferenceTactics;

    StringProcessorManager preFormatter;
    StringProcessorManager postFormatter;

    friend class ProofAssistant;
    friend class TheoryBuilder;
    friend class ProgramManager;
    friend QDataStream &operator <<(QDataStream &stream, const Theory &theory);
};

QDataStream &operator <<(QDataStream &stream, const Theory &theory);
QDataStream &operator >>(QDataStream &stream, Theory &theory);
QDataStream &operator <<(QDataStream &stream, const shared_ptr<Signature> &signature);
QDataStream &operator >>(QDataStream &stream,  shared_ptr<Signature> &signature);
QDataStream &operator <<(QDataStream &stream, const QVector<shared_ptr<StringProcessor>> &processors);
QDataStream &operator >>(QDataStream &stream, QVector<shared_ptr<StringProcessor>> &processors);

#endif // THEORY_H
