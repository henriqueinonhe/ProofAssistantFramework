#ifndef DUMMYCLASSES_H
#define DUMMYCLASSES_H

#include "inferencerule.h"
#include "lineofproof.h"
#include "inferencetactic.h"
#include "stringprocessor.h"
#include "proofprinter.h"
#include <QDataStream>

class DummyInferenceRule : public InferenceRule
{
public:
    QString name() const override
    {
        return "Dummy Inference Rule";
    }
    QString callCommand() const override
    {
        return "Dummy Call Command";
    }

    // InferenceRule interface
public:
    ~DummyInferenceRule()
    {

    }

    // InferenceRule interface
public:
    shared_ptr<LineOfProof> apply(const Parser &, Proof &, const QStringList &) const override
    {

    }
};

class DummyInferenceTactic : public InferenceTactic
{
public:


    // InferenceProcedure interface
public:
    QString name() const override
    {
        return "Dummy Inference Tactic";
    }
    QString callCommand() const override
    {
        return "Dummy Call Command";
    }

    // InferenceTactic interface
public:
    void apply(const ProofAssistant * const, const QStringList &) override
    {

    }
};

class DummyPreProcessor : public StringProcessor
{

    // StringProcessor interface
public:
    DummyPreProcessor(const Signature * const signature) :
        StringProcessor(signature)
    {

    }

    QString processString(const QString &string) const override
    {
        return string;
    }
    QString toString() const override
    {
        return "Dummy Pre Processor";
    }

    // StringProcessor interface
protected:
    void serialize(QDataStream &) const override
    {
    }
    void deserialize(QDataStream &) override
    {
    }
};

class DummyPostProcessor : public StringProcessor
{
public:
    DummyPostProcessor(const Signature * const signature) :
        StringProcessor(signature)
    {

    }

    QString processString(const QString &string) const override
    {
        return string;
    }
    QString toString() const override
    {
        return "Dummy Post Processor";
    }

    // StringProcessor interface
protected:
    void serialize(QDataStream &) const override
    {

    }
    void deserialize(QDataStream &) override
    {

    }
};

class DummyProofPrinter : public ProofPrinter
{

};

#endif // DUMMYCLASSES_H
