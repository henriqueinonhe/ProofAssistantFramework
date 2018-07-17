#include "lineofproof.h"

LineOfProof::LineOfProof()
{

}

QString LineOfProof::getSentence() const
{
    return sentence;
}

void LineOfProof::setSentence(const QString &value)
{
    sentence = value;
}

QString LineOfProof::getComment() const
{
    return comment;
}

void LineOfProof::setComment(const QString &value)
{
    comment = value;
}
