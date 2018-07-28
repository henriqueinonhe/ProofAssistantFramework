#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include "logicalsystem.h"
#include "theory.h"
#include "proof.h"
#include "storagemanager.h"
#include <memory>

using namespace std;

class ProgramManager
{
public:
    ProgramManager();

    //Logical System
    void loadLogicalSystem(const QString &name);
    LogicalSystem *getActiveLogicalSystem() const;
    void createLogicalSystem(const QString &name,
                             const QString &description,
                             const QStringList &inferenceRuleNamesList, const Type &wffType) const;
    void removeLogicalSystem(const QString &name) const;
    bool checkLogicalSystemNameCollision(const QString &name) const;
    //TODO Edit Logical System

    //Theory
    void loadTheory(const QString &name);
    Theory *getActiveTheory() const;
    void createTheory(const QString &name,
                      const QString &description,
                      const QLinkedList<Formula> axioms, const QString &signaturePluginName,
                      const QStringList &inferenceTacticsPluginsNameList,
                      const QStringList &preProcessorPluginsNameList,
                      const QStringList &postProcessorPluginsNameList) const;
    void removeTheory(const QString &theoryName) const;
    bool checkTheoryNameCollision(const QString &logicalSystemName, const QString &name) const;

private:
    void checkActiveLogicalSystem() const;
    void checkActiveTheory() const;

    QVector<LogicalSystemRecord> getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const;
    QVector<TheoryRecord> getTheoryRecordsWithoutRemovedRecord(const QString &logicalSystemName, const QString &theoryName) const;

    unique_ptr<LogicalSystem> activeLogicalSystem;
    unique_ptr<Theory> activeTheory;
};

#endif // PROGRAMMANAGER_H
