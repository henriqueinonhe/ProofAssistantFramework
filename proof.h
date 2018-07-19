#ifndef PROOF_H
#define PROOF_H

#include "formula.h"
#include "lineofproof.h"
#include "prooflinks.h"
#include "lineofproofsection.h"
#include "lineofproofsectionmanager.h"

class ProofAssistant;

class Proof
{
public:
    Proof();

    QVector<ProofLinks> getPremisesLinks() const;
    ProofLinks getConclusionLinks() const;

    bool isFinished() const;

    QString getName() const;
    void setName(const QString &value);

    QVector<const Formula *> getPremises() const;
    const Formula *getConclusion() const;

private:
    QString name;
    QVector<ProofLinks> premisesLinks;
    ProofLinks conclusionLinks;
    QVector<shared_ptr<LineOfProof>> linesOfProof;
    LineOfProofSectionManager sectioning;
    bool linkedWithAxioms; //NOTE Maybe find a better name

    friend class ProofAssistant;
};

#endif // PROOF_H
