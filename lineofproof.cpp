#include "lineofproof.h"
#include "formula.h"
#include <QDataStream>
#include "qtclassesdeserialization.h"
#include <typeinfo>

LineOfProof::LineOfProof(QDataStream &stream, const Signature * const signature) :
    formula(stream, signature),
    justification(stream),
    comment(QtDeserialization::deserializeQString(stream))
{
}

QVector<shared_ptr<LineOfProof>> LineOfProof::deserializeVector(QDataStream &stream, const Signature * const signature)
{
    int size;
    stream >> size;

    QVector<shared_ptr<LineOfProof>> vec;
    for(auto index = 0; index < size; index++)
    {
        vec.push_back(make_shared<LineOfProof>(stream, signature));
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
    if(typeid(*this) != typeid(other))
    {
        return false;
    }
    else
    {
        return isEqual(other);
    }
}

bool LineOfProof::operator!=(const LineOfProof &other) const
{
    return !(*this == other);
}

QString LineOfProof::getComment() const
{
    return comment;
}

void LineOfProof::setComment(const QString &value)
{
    comment = value;
}

bool LineOfProof::isEqual(const LineOfProof &other) const
{
    return this->formula == other.formula &&
           this->justification == other.justification &&
           this->comment == other.comment;
}

Justification LineOfProof::getJustification() const
{
    return justification;
}

Formula LineOfProof::getFormula() const
{
    return formula;
}

QDataStream &operator <<(QDataStream &stream, const LineOfProof &lineOfProof)
{
    stream << lineOfProof.formula << lineOfProof.justification << lineOfProof.comment;
    return stream;
}

QDataStream &operator <<(QDataStream &stream, const shared_ptr<LineOfProof> &lineOfProof)
{
    stream << lineOfProof->formula << lineOfProof->justification << lineOfProof->comment;
    return stream;
}

