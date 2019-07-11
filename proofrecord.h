#ifndef PROOFRECORD_H
#define PROOFRECORD_H

#include <QString>
#include <prooflinks.h>

class QDataStream;
class Formula;
class StorageManager;

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
    void addPremissLinkId(const Formula &formula, const unsigned int id);

    ProofLinks getConclusionLinks() const;
    void addConclusionLinkId(const unsigned int id);

    bool getProofIsDone() const;

private:
    ProofRecord();

    unsigned int id;
    QString name;
    QString description;
    QVector<ProofLinks> premisesLinks;
    ProofLinks conclusionLinks;
    bool proofIsDone;

    friend class QVector<ProofRecord>;
    friend QDataStream &operator <<(QDataStream &stream, const ProofRecord &record);
    friend QDataStream &operator >>(QDataStream &stream, ProofRecord &record);
    friend QDataStream &operator >>(QDataStream &stream, QVector<ProofRecord> &records);
};

QDataStream &operator <<(QDataStream &stream, const ProofRecord &record);
QDataStream &operator >>(QDataStream &stream, ProofRecord &record);
QDataStream &operator >>(QDataStream &stream, QVector<ProofRecord> &vec);

#endif // PROOFRECORD_H
