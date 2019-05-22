#ifndef PROOFRECORD_H
#define PROOFRECORD_H

#include <QString>
#include <prooflinks.h>

class QDataStream;

class ProofRecord
{
public:
    ProofRecord(QDataStream &stream);
    ProofRecord(const QString &name,
                const QString &description,
                const QVector<ProofLinks> &premisesLinks,
                const ProofLinks &conclusionLinks);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QVector<ProofLinks> getPremisesLinks() const;

    ProofLinks getConclusionLinks() const;

    bool getProofIsDone() const;

private:
    QString name;
    QString description;
    QVector<ProofLinks> premisesLinks;
    ProofLinks conclusionLinks;
    bool proofIsDone;

    friend QDataStream &operator <<(QDataStream &stream, const ProofRecord &record);
    friend QDataStream &operator >>(QDataStream &stream, ProofRecord &record);
};

QDataStream &operator <<(QDataStream &stream, const ProofRecord &record);
QDataStream &operator >>(QDataStream &stream, ProofRecord &record);

#endif // PROOFRECORD_H
