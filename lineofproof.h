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
    LineOfProof() = delete;
    LineOfProof &operator =(const LineOfProof &) = delete;
    LineOfProof &operator =(LineOfProof &&) = delete;
    ~LineOfProof() noexcept = default;

    LineOfProof(const Formula &formula, const Justification &justification, const QString &comment = "");
    LineOfProof(QDataStream &stream, Signature * const signature);
    static QVector<shared_ptr<LineOfProof> > deserializeVector(QDataStream &stream, Signature * const signature);

    bool operator==(const LineOfProof &other) const;
    bool operator!=(const LineOfProof &other) const;

    Formula getFormula() const;

    Justification getJustification() const;

    QString getComment() const;
    void setComment(const QString &value);

protected:
    LineOfProof(const LineOfProof &) = default;
    LineOfProof(LineOfProof &&) noexcept = default;

    virtual bool isEqual(const LineOfProof &other) const;

    Formula formula;
    Justification justification;
    QString comment;

    friend class QVector<LineOfProof>;
    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const shared_ptr<LineOfProof> &lineOfProof);
    friend QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof);
};

QDataStream &operator <<(QDataStream &stream, const shared_ptr<LineOfProof> &lineOfProof);
QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof);

#endif // LINEOFPROOF_H
