#ifndef PROOFTESTER_H
#define PROOFTESTER_H

#include "proof.h"

class ProofTester
{
public:
    ProofTester(Proof &testProof);
    void addLineOfProof(const shared_ptr<LineOfProof> &lineOfProof);

    Proof &proof;
};

#endif // PROOFTESTER_H
