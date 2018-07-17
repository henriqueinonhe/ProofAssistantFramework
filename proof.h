﻿#ifndef PROOF_H
#define PROOF_H

#include "formula.h"
#include "lineofproof.h"
#include "prooflinks.h"
#include "tree.h"

class Proof
{
public:
    Proof();

    QVector<ProofLinks> &getPremisesLinks();
    ProofLinks &getConclusionLinks();

    bool isFinished() const;

    QString getName() const;
    void setName(const QString &value);

    QVector<const Formula *> getPremises() const;
    const Formula *getConclusion() const;

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

    QString name;
    QVector<ProofLinks> premisesLinks;
    ProofLinks conclusionLinks;
    QVector<LineOfProof> demonstration; //FIXME Becomes either a linked list or wrap LineOfProof with a shared pointer
    Tree<LineOfProofSection> sectioning; //TODO
    bool linkedWithAxioms; //NOTE Maybe find a better name
};

#endif // PROOF_H
