#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include "logicalsystem.h"
#include "theory.h"
#include "theorybuilder.h"
#include "proof.h"
#include "storagemanager.h"
#include "proofassistant.h"
#include <memory>

using namespace std;

class ProgramManager
{
public:
    ProgramManager();

    //Logical System
    void createLogicalSystem(const QString &name,
                             const QString &description,
                             const QString &signaturePluginName,
                             const QStringList &inferenceRulesNamesList,
                             const Type &wffType) const;
    void loadLogicalSystem(const QString &name);
    void removeLogicalSystem(const QString &name) const;
    bool checkLogicalSystemNameCollision(const QString &name) const;
    LogicalSystem *getActiveLogicalSystem() const;
    //TODO Edit Logical System

    //Theory
    void createTheory(const TheoryBuilder &builder) const;
    void loadTheory(const QString &name);
    void removeTheory(const QString &theoryName) const;
    bool checkTheoryNameCollision(const QString &logicalSystemName, const QString &name) const;
    Theory *getActiveTheory() const;
    //TODO Edit Theory

    //Proof
    //void createProof(const QString &string);

private:
    void checkActiveLogicalSystem() const;
    void checkActiveTheory() const;

    QVector<LogicalSystemRecord> getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const;
    QVector<TheoryRecord> getTheoryRecordsWithoutRemovedRecord(const QString &logicalSystemName, const QString &theoryName) const;

    unique_ptr<LogicalSystem> activeLogicalSystem;
    unique_ptr<Theory> activeTheory;
};

#endif // PROGRAMMANAGER_H
