#ifndef LINEOFPROOF_H
#define LINEOFPROOF_H

#include <QString>
#include <memory>
#include "justification.h"

class Formula;
class ProofAssistant;

using namespace std;

class LineOfProof
{
public:
    LineOfProof();

    LineOfProof(const Formula &formula, const Justification &justification, const QString &comment = "");

    Formula getFormula() const;
    void setFormula(const Formula &formula);

    Justification getJustification() const;
    void setJustification(const Justification &value);

    QString getComment() const;
    void setComment(const QString &value);

protected:
    unique_ptr<Formula> formula;
    Justification justification;
    QString comment;

    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof);
    friend QDataStream &operator >>(QDataStream &stream, const LineOfProof &lineOfProof);
};

QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof);
QDataStream &operator >>(QDataStream &stream, const LineOfProof &lineOfProof);

#endif // LINEOFPROOF_H
