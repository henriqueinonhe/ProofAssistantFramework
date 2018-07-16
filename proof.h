#ifndef PROOF_H
#define PROOF_H

#include "formula.h"
#include "lineofproof.h"
#include "prooflinks.h"
#include "tree.h"

class Proof
{
public:
    Proof();

private:
    struct LineOfProofSection
    {
        LineOfProofSection(const unsigned int beginIndex,
                           const unsigned int endIndex,
                           const QString &label,
                           const bool collapsed) :
            beginIndex(beginIndex),
            endIndex(endIndex),
            label(label),
            collapsed(collapsed)
        {}

        LineOfProofSection(){}

        unsigned int beginIndex;
        unsigned int endIndex;
        QString label;
        bool collapsed;
    };

    QVector<ProofLinks> premisesLinks;
    ProofLinks conclusionLinks;
    QVector<LineOfProof> demonstration;
    Tree<LineOfProofSection> sectioning;
    bool linkedWithAxioms; //NOTE Maybe find a better name
};

#endif // PROOF_H
