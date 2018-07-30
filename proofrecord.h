#ifndef PROOFRECORD_H
#define PROOFRECORD_H

#include <QString>
#include <QStringList>

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
};

#endif // PROOFRECORD_H
