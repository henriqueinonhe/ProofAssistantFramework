//#ifndef PROGRAMMANAGER_H
//#define PROGRAMMANAGER_H

//#include <memory>
//#include "theory.h"
//#include "logicalsystem.h"
//#include "theorypluginsrecord.h"
//#include "logicalsystempluginsrecord.h"

//class LogicalSystem;
//class Type;
//class Theory;
//class TheoryBuilder;
//class LogicalSystemRecord;
//class TheoryRecord;
//class ProofRecord;

//using namespace std;

//class ProgramManager
//{
//public:
//    static const QString defaultProofPluginName;

//    ProgramManager();

//    //Logical System
//    void createLogicalSystem(const QString &name,
//                             const QString &description,
//                             const QStringList &inferenceRulesNamesList,
//                             const QString &signaturePluginName,
//                             const QString &proofName,
//                             const Type &wffType) const;
//    void loadLogicalSystem(const QString &name);
//    void unloadLogicalSystem();
//    void removeLogicalSystem(const QString &name) const;
//    bool checkLogicalSystemNameCollision(const QString &name) const;
//    LogicalSystem *getActiveLogicalSystem() const;
//    //TODO Edit Logical System

//    //Theory
//    void createTheory(const TheoryBuilder &builder, const TheoryPluginsRecord &pluginsRecord) const;
//    void loadTheory(const QString &name);
//    void unloadTheory();
//    void removeTheory(const QString &theoryName) const;
//    bool checkTheoryNameCollision(const QString &logicalSystemName, const QString &name) const;
//    Theory *getActiveTheory() const;
//    //TODO Edit Theory

//     //Theory Plugins
//    void addPreProcessorPlugin(const QString &processorPluginName) const;
//    void addPostProcessorPlugin(const QString &processorPluginName) const;
//    void removePreProcessorPlugin(const unsigned int processorIndex) const;
//    void removePostProcessorPlugin(const unsigned int processorIndex) const;
//    void addInferenceTacticPlugin(const QString &tacticPluginName) const;
//    void removeInferenceTacticPlugin(const unsigned int tacticIndex) const;

//    //Proof
//    void createProof(const QString &name,
//                     const QString &description,
//                     const QStringList &premises,
//                     const QString &conclusion) const;
//    ProofAssistant loadProof(const unsigned int proofId) const;
//    void saveProof(const ProofAssistant &assistant) const;

//private:
//    void checkActiveLogicalSystem() const;
//    void checkActiveTheory() const;

//    LogicalSystemPluginsRecord retrieveActiveLogicalSystemPluginsRecord() const;
//    void storeActiveLogicalSystemPluginsRecord(const LogicalSystemPluginsRecord &pluginsRecord) const;
//    TheoryPluginsRecord retrieveActiveTheoryPluginsRecord() const;
//    void storeActiveTheoryPluginsRecord(const TheoryPluginsRecord &pluginsRecord) const;

//    QVector<shared_ptr<const InferenceRule> > loadInferenceRules(const QStringList &inferenceRulesNames) const;
//    shared_ptr<Signature> loadSignature(const QString &signatureName) const;
//    shared_ptr<Proof> loadProofPlugin(const QString &proofPluginName, const uint id, const QString &name, const QString &description, const QVector<Formula> &premises, const Formula &conclusion) const;
//    void testLoadProofPlugin(const QString &proofPluginName) const;

//    QVector<Formula> makePremisesFormulas(const QStringList &premises, const Parser *parser) const;
//    QVector<ProofLinks> linkPremises(const unsigned int currentProofId, const QVector<Formula> &premises, QVector<ProofRecord> &proofsRecords) const;
//    ProofLinks linkConclusion(const unsigned int currentProofId, const Formula &conclusion, QVector<ProofRecord> &proofsRecords) const;

//    QVector<LogicalSystemRecord> getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const;
//    QVector<TheoryRecord> getTheoryRecordsWithoutRemovedRecord(const QString &logicalSystemName, const QString &theoryName) const;

//    unique_ptr<LogicalSystem> activeLogicalSystem;
//    unique_ptr<Theory> activeTheory;
//};



//#endif // PROGRAMMANAGER_H
