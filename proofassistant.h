#ifndef PROOFASSISTANT_H
#define PROOFASSISTANT_H

#include "theory.h"
#include "prooflinks.h"
#include <memory>

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
    void addPremise(const QString &premise);

private:
    void checkCurrentTheoryIsNull() const;
    void checkCurrentProofIsNull() const;

    Theory *currentTheory;
    Proof *currentProof;
    bool proofOwner; //WTF! What is this again?
    void createPremiseLineOfProof(const Formula &parsedPremise);
    void linkPremise(const QString &premise);
};

#endif // PROOFASSISTANT_H
