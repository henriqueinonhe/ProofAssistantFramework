#ifndef PROGRAMASSISTANT_H
#define PROGRAMASSISTANT_H

class Type;
class Signature;
class Formula;
class Proof;
class InferenceRule;
class LogicalSystemRecord;
namespace std
{
    template <class> class shared_ptr;
}

using namespace std;

class ProgramAssistant
{
public:
    ProgramAssistant();

    //Logical System
    void createLogicalSystem(const QString &name,
                             const QString &description,
                             const QStringList &inferenceRulesNamesList,
                             const QString &signaturePluginName,
                             const QString &proofName,
                             const Type &wffType) const;
    void loadLogicalSystem(const QString &name);
    void removeLogicalSystem(const QString &name) const;
    bool checkLogicalSystemNameCollision(const QString &name) const;

private:
    QVector<shared_ptr<const InferenceRule> > loadInferenceRules(const QStringList &inferenceRulesNames) const;
    shared_ptr<Signature> loadSignature(const QString &signatureName) const;
    shared_ptr<Proof> loadProofPlugin(const QString &proofPluginName, const uint id, const QString &name, const QString &description, const QVector<Formula> &premises, const Formula &conclusion) const;
    void testLoadProofPlugin(const QString &proofPluginName) const;

    QVector<LogicalSystemRecord> getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const;
};

#endif // PROGRAMASSISTANT_H
