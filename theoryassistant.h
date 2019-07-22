#ifndef THEORYASSISTANT_H
#define THEORYASSISTANT_H

#include "theory.h"
#include "logicalsystem.h"

class Theory;
class ProofAssistant;
class TheoryPluginsRecord;
class ProofLinks;
class Formula;
class Parser;
class ProofRecord;
class Proof;

namespace std
{
    template<class> class shared_ptr;
}

using namespace std;

class TheoryAssistant
{
public:
    TheoryAssistant(const LogicalSystem &activeLogicalSystem, Theory &&activeTheory);

    //Theory
    const Theory &getActiveTheory() const;
    //TODO Edit Theory

     //Theory Plugins
    Signature &accessSignaturePlugin();
    void addPreProcessorPlugin(const QString &processorPluginName);
    void addPostProcessorPlugin(const QString &processorPluginName);
    void removePreProcessorPlugin(const unsigned int processorIndex);
    void removePostProcessorPlugin(const unsigned int processorIndex);
    void addInferenceTacticPlugin(const QString &tacticPluginName);
    void removeInferenceTacticPlugin(const unsigned int tacticIndex);

    //Proof
    void createProof(const QString &name,
                     const QString &description,
                     const QStringList &premises,
                     const QString &conclusion) const;
    ProofAssistant loadProof(const unsigned int proofId) const;

private:
    TheoryPluginsRecord retrieveActiveTheoryPluginsRecord() const;
    void storeActiveTheoryPluginsRecord(const TheoryPluginsRecord &pluginsRecord) const;
    shared_ptr<Proof> loadProofPlugin(const QString &proofPluginName, const uint id, const QString &name, const QString &description, const QVector<Formula> &premises, const Formula &conclusion) const;
    QVector<Formula> makePremisesFormulas(const QStringList &premises, const Parser *parser) const;
    QVector<ProofLinks> linkPremises(const unsigned int currentProofId, const QVector<Formula> &premises, QVector<ProofRecord> &proofsRecords) const;
    ProofLinks linkConclusion(const unsigned int currentProofId, const Formula &conclusion, QVector<ProofRecord> &proofsRecords) const;

    const LogicalSystem &activeLogicalSystem;
    Theory activeTheory;
};

#endif // THEORYASSISTANT_H
