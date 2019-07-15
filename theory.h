#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "parser.h"
#include "signature.h"
#include "formatter.h"

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
    QVector<shared_ptr<StringProcessor>> &getPreProcessorsOld();
    QVector<shared_ptr<StringProcessor>> &getPostProcessorsOld();
    const QVector<shared_ptr<const InferenceTactic>> &getInferenceTactics() const;
    const QVector<shared_ptr<StringProcessor>> &getPreProcessorsOld()  const;
    const QVector<shared_ptr<StringProcessor>> &getPostProcessorsOld() const;

    //String Processors
    QVector<StringProcessor *> getPreProcessors() const;
    QVector<StringProcessor *> getPostProcessors() const;

    void addPreProcessor(const shared_ptr<StringProcessor> &preProcessor);
    void addPostProcessor(const shared_ptr<StringProcessor> &postProcessor);
    void turnOnPreProcessor(const unsigned int index);
    void turnOnPostProcessor(const unsigned int index);
    void turnOffPreProcessor(const unsigned int index);
    void turnOffPostProcessor(const unsigned int index);
    void togglePreProcessor(const unsigned int index);
    void tooflePostProcessor(const unsigned int index);
    void removePreProcessor(const unsigned int index);
    void removePostProcessor(const unsigned int index);

    Formatter getPreFormatter() const;
    Formatter getPostFormatter() const;

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
QDataStream &operator <<(QDataStream &stream, const QVector<shared_ptr<StringProcessor>> &processors);
QDataStream &operator >>(QDataStream &stream, QVector<shared_ptr<StringProcessor>> &processors);

#endif // THEORY_H
