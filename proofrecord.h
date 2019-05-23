#ifndef PROOFRECORD_H
#define PROOFRECORD_H

#include <QString>
#include <prooflinks.h>

class QDataStream;
class Formula;

class ProofRecord
{
public:
    ProofRecord(QDataStream &stream);
    ProofRecord(const unsigned int id,
                const QString &name,
                const QString &description,
                const QVector<ProofLinks> &premisesLinks,
                const ProofLinks &conclusionLinks);

    unsigned int getId() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QStringList getPremises() const;
    QString getConclusion() const;

    QVector<ProofLinks> getPremisesLinks() const;

    ProofLinks getConclusionLinks() const;

    bool getProofIsDone() const;

private:
    unsigned int id;
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
