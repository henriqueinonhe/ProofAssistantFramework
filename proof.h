#ifndef PROOF_H
#define PROOF_H

#include "formula.h"
#include "lineofproof.h"
#include "prooflinks.h"
#include "lineofproofsection.h"
#include "lineofproofsectionmanager.h"
#include <QDataStream>

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

    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const Proof &proof);
    friend QDataStream &operator >>(QDataStream &stream, Proof &proof);
};

QDataStream &operator <<(QDataStream &stream, const Proof &proof);
QDataStream &operator >>(QDataStream &stream, Proof &proof);

#endif // PROOF_H
