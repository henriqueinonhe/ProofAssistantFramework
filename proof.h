#ifndef PROOF_H
#define PROOF_H

#include "lineofproof.h"
#include "prooflinks.h"
#include "lineofproofsectionmanager.h"

class Formula;
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

    QVector<Formula> getPremises() const;
    Formula getConclusion() const;

private:
    unsigned int id;
    QString name;
    QString description;
    QVector<ProofLinks> premisesLinks;
    ProofLinks conclusionLinks;
    QVector<LineOfProof> linesOfProof;
    LineOfProofSectionManager sectioning;
    bool linkedWithAxioms;

    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const Proof &proof);
    friend QDataStream &operator >>(QDataStream &stream, Proof &proof);
};

QDataStream &operator <<(QDataStream &stream, const Proof &proof);
QDataStream &operator >>(QDataStream &stream, Proof &proof);

#endif // PROOF_H
