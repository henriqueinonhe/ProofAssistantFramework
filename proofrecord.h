#ifndef PROOFRECORD_H
#define PROOFRECORD_H

#include <QString>
#include <QStringList>

class QDataStream;

//NOTE Maybe use formulas here...

class ProofRecord
{
public:
    ProofRecord();
    ProofRecord(const QString &name,
                const QString &description,
                const QStringList &premises,
                const QString conclusion);

private:
    QString name;
    QString description;
    QStringList premises;
    QString conclusion;

    friend QDataStream &operator <<(QDataStream &stream, const ProofRecord &record);
    friend QDataStream &operator >>(QDataStream &stream, ProofRecord &record);
};

QDataStream &operator <<(QDataStream &stream, const ProofRecord &record);
QDataStream &operator >>(QDataStream &stream, ProofRecord &record);

#endif // PROOFRECORD_H
