#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include <memory>
#include "theory.h"
#include "logicalsystem.h"
#include "theorypluginsrecord.h"

class LogicalSystem;
class Type;
class Theory;
class TheoryBuilder;
class LogicalSystemRecord;
class TheoryRecord;
class ProofRecord;

using namespace std;

class ProgramManager
{
public:
    ProgramManager();

    //Logical System
    void createLogicalSystem(const QString &name,
                             const QString &description,
                             const QStringList &inferenceRulesNamesList,
                             const Type &wffType) const;
    void loadLogicalSystem(const QString &name);
    void removeLogicalSystem(const QString &name) const;
    bool checkLogicalSystemNameCollision(const QString &name) const;
    LogicalSystem *getActiveLogicalSystem() const;
    //TODO Edit Logical System

    //Theory
    void createTheory(const TheoryBuilder &builder, const TheoryPluginsRecord &pluginsRecord) const;
    void loadTheory(const QString &name);
    void removeTheory(const QString &theoryName) const;
    bool checkTheoryNameCollision(const QString &logicalSystemName, const QString &name) const;
    Theory *getActiveTheory() const;
    //TODO Edit Theory

    //Proof
    void createProof(const QString &name,
                     const QString &description,
                     const QStringList &premises,
                     const QString &conclusion) const;
    ProofAssistant loadProof(const unsigned int proofId) const;
    void saveProof(const ProofAssistant &assistant) const;


private:
    void checkActiveLogicalSystem() const;
    void checkActiveTheory() const;
    void loadInferenceRules(const QStringList &inferenceRulesNames, QVector<shared_ptr<const InferenceRule>> &inferenceRules) const;
    void makePremisesFormulas(const QStringList &premises, QVector<Formula> &premisesFormulas, Parser *parser) const;
    void linkPremises(const QStringList &premises, const QVector<ProofRecord> &proofsRecords, QVector<ProofLinks> &premisesLinks) const;
    ProofLinks linkConclusion(const QString &conclusion, const QVector<ProofRecord> &proofsRecords) const;

    QVector<LogicalSystemRecord> getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const;
    QVector<TheoryRecord> getTheoryRecordsWithoutRemovedRecord(const QString &logicalSystemName, const QString &theoryName) const;

    unique_ptr<LogicalSystem> activeLogicalSystem;
    unique_ptr<Theory> activeTheory;
    TheoryPluginsRecord theoryPluginsRecord;
};



#endif // PROGRAMMANAGER_H
