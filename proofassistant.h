#ifndef PROOFASSISTANT_H
#define PROOFASSISTANT_H

#include "logicalsystem.h"
#include "theory.h"
#include "prooflinks.h"
#include <memory>

//FIXME Gotta rework whole class!

class ProofAssistant
{
public:
    ProofAssistant();

    void createProof();
    void setProofName(const QString &name);
    void addPremise(const QString &premise);
    //TODO removePremise();

    void applyInferenceRule(const QString &callCommand, const QStringList &argumentList) const;
    void applyInferenceTactic(const QString &callCommand, const QStringList &argumentList) const;

    void setLineOfProofComment(const unsigned int lineNumber, const QString &comment) const;

private:
    template <class T>
    T *queryInferenceProcedure(const QVector<T *> &procedureList, const QString &callCommand) const
    {
        T *procedure = nullptr;

        std::for_each(procedureList.begin(), procedureList.end(), [&callCommand, &procedure](T * const &storedProcedure)
        {
            if(callCommand == storedProcedure->callCommand())
            {
                procedure = storedProcedure;
            }
        });

        return procedure;
    }

    void createPremiseLineOfProof(const Formula &parsedPremise);
    void linkPremise(const QString &premise);
};

#endif // PROOFASSISTANT_H
