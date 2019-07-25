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
class LogicalSystemPluginsRecord;
class ProofPrinter;

namespace std
{
    template<class> class shared_ptr;
}

using namespace std;

class TheoryAssistant
{
public:
    TheoryAssistant(const LogicalSystem &activeLogicalSystem, Theory &&activeTheory, const shared_ptr<ProofPrinter> &proofPrinter);

    //Logical System
    const LogicalSystem &getActiveLogicalSystem() const;
    const ProofPrinter &getProofPrinter() const;

    //Theory
    const Theory &getActiveTheory() const;
    //TODO Edit Theory

     //Theory Plugins
    Signature *accessSignaturePlugin();
    void addPreProcessorPlugin(const QString &processorPluginName);
    void addPostProcessorPlugin(const QString &processorPluginName);
    void removePreProcessorPlugin(const unsigned int processorIndex);
    void removePostProcessorPlugin(const unsigned int processorIndex);
    void turnOnPreProcessorPlugin(const unsigned int processorIndex);
    void turnOnPostProcessorPlugin(const unsigned int processorIndex);
    void turnOffPreProcessorPlugin(const unsigned int processorIndex);
    void turnOffPostProcessorPlugin(const unsigned int processorIndex);
    QStringList listLoadedPreProcessors() const;
    QStringList listLoadedPostProcessors() const;
    void addInferenceTacticPlugin(const QString &tacticPluginName);
    void removeInferenceTacticPlugin(const unsigned int tacticIndex);

    //Proof
    void createProof(const QString &name,
                     const QString &description,
                     const QStringList &premises,
                     const QString &conclusion) const;
    ProofAssistant loadProof(const unsigned int proofId) const;
    void saveProof(const ProofAssistant &assistant) const;


private:
    LogicalSystemPluginsRecord retrieveActiveLogicalSystemPluginsRecord() const;
    TheoryPluginsRecord retrieveActiveTheoryPluginsRecord() const;
    void storeActiveTheoryPluginsRecord(const TheoryPluginsRecord &pluginsRecord) const;
    shared_ptr<Proof> loadProofPlugin(const QString &proofPluginName, const uint id, const QString &name, const QString &description, const QVector<Formula> &premises, const Formula &conclusion) const;
    QVector<Formula> makePremisesFormulas(const QStringList &premises, const Parser &parser) const;
    QVector<ProofLinks> linkPremises(const unsigned int currentProofId, const QVector<Formula> &premises, QVector<ProofRecord> &proofsRecords) const;
    ProofLinks linkConclusion(const unsigned int currentProofId, const Formula &conclusion, QVector<ProofRecord> &proofsRecords) const;

    const LogicalSystem &activeLogicalSystem;
    Theory activeTheory;
    shared_ptr<ProofPrinter> proofPrinter;
};

#endif // THEORYASSISTANT_H
