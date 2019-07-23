#ifndef PROOFASSISTANT_H
#define PROOFASSISTANT_H

#include "proof.h"

class Formula;
class Proof;
class LogicalSystem;
class Theory;

namespace std
{
    template <class T> class shared_ptr;
}

class ProofAssistant
{
public:
    ProofAssistant() = delete;
    ProofAssistant(const Theory &theory, const shared_ptr<Proof> &proof);

    void applyInferenceRule(const QString &callCommand, const QStringList &argumentList);
    void applyInferenceTactic(const QString &callCommand, const QStringList &argumentList) const;
    void setLineOfProofComment(const unsigned int lineNumber, const QString &comment);

    const Proof &getProof() const;

private:
    template <class T>
    T *queryInferenceProcedure(const QVector<std::shared_ptr<T>> &procedureList, const QString &callCommand) const
    {
        T *procedure = nullptr;

        for(const std::shared_ptr<T> &storedProcedure : procedureList)
        {
            if(callCommand == storedProcedure->callCommand())
            {
                procedure = storedProcedure.get();
            }
        }
        return procedure;
    }

    const Theory &theory;
    shared_ptr<Proof> proof;
};

#endif // PROOFASSISTANT_H
