#ifndef PROOFASSISTANT_H
#define PROOFASSISTANT_H

#include "theory.h"

class ProofAssistant
{
public:
    ProofAssistant();

    Theory *getCurrentTheory() const;
    void setCurrentTheory(Theory *value);

    Proof *getCurrentProof() const;
    void setCurrentProof(Proof *value);

    void createProof();
    void setProofName(const QString &name);
    void addPremiss(const QString &premiss);

private:
    void checkCurrentTheoryIsNull() const;
    void checkCurrentProofIsNull() const;

    Theory *currentTheory;
    Proof *currentProof;
    bool proofOwner;
};

#endif // PROOFASSISTANT_H
