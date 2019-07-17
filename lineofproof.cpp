#include "lineofproof.h"
#include "formula.h"
#include <QDataStream>

LineOfProof::LineOfProof(QDataStream &stream, Signature * const signature) :
    formula(stream, signature)
{
    stream >> justification >> comment;
}

QVector<LineOfProof> LineOfProof::deserializeVector(QDataStream &stream, Signature * const signature)
{
    int size;
    stream >> size;

    QVector<LineOfProof> vec;
    for(auto index = 0; index < size; index++)
    {
        vec.push_back(LineOfProof(stream, signature));
    }
    return vec;
}

LineOfProof::LineOfProof(const Formula &formula, const Justification &justification, const QString &comment) :
    formula(formula),
    justification(justification),
    comment(comment)
{

}

bool LineOfProof::operator==(const LineOfProof &other) const
{
    return this->formula == other.formula &&
           this->justification == other.justification &&
           this->comment == other.comment;
}

bool LineOfProof::operator!=(const LineOfProof &other) const
{
    return !(*this == other);
}

const QString &LineOfProof::getComment() const
{
    return comment;
}

void LineOfProof::setComment(const QString &value)
{
    comment = value;
}

LineOfProof::LineOfProof()
{

}

const Justification &LineOfProof::getJustification() const
{
    return justification;
}

const Formula &LineOfProof::getFormula() const
{
    return formula;
}

QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof)
{
    stream << lineOfProof.formula << lineOfProof.justification << lineOfProof.comment;
    return stream;
}

