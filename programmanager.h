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

    LogicalSystem *getActiveLogicalSystem() const;

    void createLogicalSystem(const QString &name,
                             const QString &description,
                             const QStringList &inferenceRuleNamesList, const Type &wffType) const;
    void removeLogicalSystem(const QString &name) const;

    void loadLogicalSystem(const QString &name);

    bool checkLogicalSystemNameCollision(const QString &name) const;

private:
    unique_ptr<LogicalSystem> activeLogicalSystem;
    Theory *activeTheory;
    QVector<LogicalSystemRecord> getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const;
};

#endif // PROGRAMMANAGER_H
