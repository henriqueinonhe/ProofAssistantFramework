#ifndef LINEOFPROOF_H
#define LINEOFPROOF_H

#include <QString>

class LineOfProof
{
public:
    LineOfProof();

    QString getSentence() const;
    void setSentence(const QString &value);

    QString getComment() const;
    void setComment(const QString &value);

private:
    QString sentence; //FIXME Gotta be something else here, probably an interface
    QString comment;
    //Justification

};

#endif // LINEOFPROOF_H
