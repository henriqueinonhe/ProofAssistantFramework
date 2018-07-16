#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "proof.h"
#include "parser.h"

class Theory
{
public:
    Theory();

    void addAxiom(const QString &axiom); //TODO
    void removeAxiom(const QString &axiom); //TODO

private:
    QString name;
    unique_ptr<Parser> parser;
    unique_ptr<Signature> signature;
    QVector<Formula> axioms;
    QLinkedList<Proof> proofs;
};

#endif // THEORY_H
