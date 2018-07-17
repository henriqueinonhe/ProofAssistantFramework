#ifndef LINEOFPROOF_H
#define LINEOFPROOF_H

#include <QString>
#include <memory>
#include "formula.h"
#include "justification.h"

using namespace std;

class LineOfProof
{
public:
    LineOfProof();

    LineOfProof(const Formula &formula, const Justification &justification, const QString &comment = "");

    Formula &getFormula();
    void setFormula(const Formula &formula);

    Justification getJustification() const;
    void setJustification(const Justification &value);

    QString getComment() const;
    void setComment(const QString &value);

private:
    unique_ptr<Formula> formula;
    Justification justification;
    QString comment;
};

#endif // LINEOFPROOF_H
