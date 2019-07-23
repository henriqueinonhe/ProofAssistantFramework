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
                             const QString &proofPrinterPluginName,
                             const Type &wffType) const;
    void loadLogicalSystem(const QString &name);
    void removeLogicalSystem(const QString &name) const;
    bool checkLogicalSystemNameCollision(const QString &name) const;

private:
    QVector<shared_ptr<const InferenceRule> > loadInferenceRulesPlugins(const QStringList &inferenceRulesNames) const;
    shared_ptr<Signature> validateSignaturePlugin(const QString &signatureName) const;
    void validateProofPlugin(const QString &proofPluginName) const;
    void validateProofPrinterPlugin(const QString &proofPrinterPluginName) const;

    QVector<LogicalSystemRecord> getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const;
};

#endif // PROGRAMASSISTANT_H
