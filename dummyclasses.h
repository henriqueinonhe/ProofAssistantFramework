#ifndef DUMMYCLASSES_H
#define DUMMYCLASSES_H

#include "inferencerule.h"
#include "lineofproof.h"
#include "inferencetactic.h"
#include "stringprocessor.h"

class DummyInferenceRule : public InferenceRule
{
public:
    QString name() const
    {
        return "Dummy Inference Rule";
    }
    QString callCommand() const
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
    LineOfProof apply(const Parser &parser, const Proof &proof, const QStringList &argumentList) const
    {

    }
};

class DummyInferenceTactic : public InferenceTactic
{
public:


    // InferenceProcedure interface
public:
    QString name() const
    {
        return "Dummy Inference Tactic";
    }
    QString callCommand() const
    {
        return "Dummy Call Command";
    }

    // InferenceTactic interface
public:
    void apply(const ProofAssistant * const assistant, const QStringList &argumentList)
    {

    }
};

class DummyPreProcessor : public StringProcessor
{

    // StringProcessor interface
public:
    QString processString(const QString &string) const
    {

    }
    QString toString() const
    {
        return "Dummy Pre Processor";
    }
};

class DummyPostProcessor : public StringProcessor
{


    // StringProcessor interface
public:
    QString processString(const QString &string) const
    {

    }
    QString toString() const
    {
        return "Dummy Post Processor";
    }
};

#endif // DUMMYCLASSES_H
