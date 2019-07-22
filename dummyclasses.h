#ifndef DUMMYCLASSES_H
#define DUMMYCLASSES_H

#include "inferencerule.h"
#include "lineofproof.h"
#include "inferencetactic.h"
#include "stringprocessor.h"

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
    shared_ptr<LineOfProof> apply(const Parser &parser, Proof &proof, const QStringList &argumentList) const override
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
    void apply(const ProofAssistant * const assistant, const QStringList &argumentList) override
    {

    }
};

class DummyPreProcessor : public StringProcessor
{

    // StringProcessor interface
public:
    QString processString(const QString &string) const override
    {

    }
    QString toString() const override
    {
        return "Dummy Pre Processor";
    }
};

class DummyPostProcessor : public StringProcessor
{


    // StringProcessor interface
public:
    QString processString(const QString &string) const override
    {

    }
    QString toString() const override
    {
        return "Dummy Post Processor";
    }
};

#endif // DUMMYCLASSES_H
