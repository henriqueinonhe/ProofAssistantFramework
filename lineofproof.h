#ifndef LINEOFPROOF_H
#define LINEOFPROOF_H

#include <QString>
#include <memory>
#include "justification.h"
#include "formula.h"

class Formula;
class ProofAssistant;

using namespace std;

class LineOfProof
{
public:
    LineOfProof(QDataStream &stream, const Signature * const signature);
    LineOfProof(const Formula &formula, const Justification &justification, const QString &comment = "");

    bool operator==(const LineOfProof &other) const;
    bool operator!=(const LineOfProof &other) const;

    Formula getFormula() const;

    Justification getJustification() const;

    QString getComment() const;
    void setComment(const QString &value);

protected:
    LineOfProof();

    Formula formula;
    Justification justification;
    QString comment;

    friend class QVector<LineOfProof>;
    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof);
    friend QDataStream &operator >>(QDataStream &stream, const LineOfProof &lineOfProof);
};

QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof);
QDataStream &operator >>(QDataStream &stream, const LineOfProof &lineOfProof);

#endif // LINEOFPROOF_H
