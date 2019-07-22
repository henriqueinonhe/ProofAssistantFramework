#include "prooftester.h"

ProofTester::ProofTester(Proof &testProof) :
    proof(testProof)
{

}

void ProofTester::addLineOfProof(const shared_ptr<LineOfProof> &lineOfProof)
{
    proof.addLineOfProof(lineOfProof);
}
