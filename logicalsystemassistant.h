#ifndef LOGICALSYSTEMASSISTANT_H
#define LOGICALSYSTEMASSISTANT_H
#include "logicalsystem.h"

class LogicalSystem;
class TheoryBuilder;
class TheoryPluginsRecord;
class LogicalSystemPluginsRecord;
class Signature;
class TheoryRecord;
class TheoryAssistant;

namespace std
{
    template <class> class shared_ptr;
}

using namespace std;

class LogicalSystemAssistant
{
public:
    LogicalSystemAssistant() = delete;
    LogicalSystemAssistant(const LogicalSystemAssistant &) = delete;
    LogicalSystemAssistant(LogicalSystemAssistant &&other) noexcept = default;
    LogicalSystemAssistant &operator =(const LogicalSystemAssistant &) = delete;
    LogicalSystemAssistant &operator =(LogicalSystemAssistant &&) = delete;
    ~LogicalSystemAssistant() noexcept = default;

    LogicalSystemAssistant(LogicalSystem &&logicalSystem);

    //Logical System
    const LogicalSystem &getActiveLogicalSystem() const;
    //TODO Edit Logical System

    //Theory
    void createTheory(const TheoryBuilder &builder, const TheoryPluginsRecord &pluginsRecord) const;
    TheoryAssistant loadTheory(const QString &name);
    void removeTheory(const QString &theoryName) const;
    bool checkTheoryNameCollision(const QString &logicalSystemName, const QString &name) const;

private:
    LogicalSystemPluginsRecord retrieveActiveLogicalSystemPluginsRecord() const;
    void storeActiveLogicalSystemPluginsRecord(const LogicalSystemPluginsRecord &pluginsRecord) const;
    shared_ptr<Signature> loadSignature(const QString &signatureName) const;
    QVector<TheoryRecord> getTheoryRecordsWithoutRemovedRecord(const QString &logicalSystemName, const QString &theoryName) const;

    LogicalSystem activeLogicalSystem;
};

#endif // LOGICALSYSTEMASSISTANT_H
