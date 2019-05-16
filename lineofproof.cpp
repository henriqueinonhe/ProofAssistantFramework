#include "lineofproof.h"
#include "formula.h"
#include <QDataStream>

LineOfProof::LineOfProof()
{

}

LineOfProof::LineOfProof(const Formula &formula, const Justification &justification, const QString &comment) :
    formula(new Formula(formula)),
    justification(justification),
    comment(comment)
{

}

QString LineOfProof::getComment() const
{
    return comment;
}

void LineOfProof::setComment(const QString &value)
{
    comment = value;
}

Justification LineOfProof::getJustification() const
{
    return justification;
}

void LineOfProof::setJustification(const Justification &value)
{
    justification = value;
}

Formula LineOfProof::getFormula() const
{
    return *formula;
}

void LineOfProof::setFormula(const Formula &formula)
{
    this->formula.reset(new Formula(formula));
}

QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof)
{
    stream << *lineOfProof.formula << lineOfProof.justification << lineOfProof.comment;
}

QDataStream &operator >>(QDataStream &stream, const LineOfProof &lineOfProof)
{
    //TODO
}
