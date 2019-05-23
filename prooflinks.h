#ifndef PROOFLINKS_H
#define PROOFLINKS_H

#include <QString>
#include <QVector>

class QDataStream;
class ProofRecord;
class ProgramManager;

class ProofLinks
{
public:
    ProofLinks(QDataStream &stream);
    ProofLinks(const QString &formula, const QVector<unsigned int> linkedProofsIds);

    QString getFormula() const;
    QVector<unsigned int> getLinkedProofsIds() const;

    bool operator==(const ProofLinks &other) const;
    bool operator!=(const ProofLinks &other) const;

private:
    ProofLinks();

    QString formula;
    QVector<unsigned int> linkedProofsIds;

    friend class ProofRecord;
    friend class QVector<ProofLinks>;
    friend QDataStream &operator <<(QDataStream &stream, const ProofLinks &links);
    friend QDataStream &operator >>(QDataStream &stream, ProofLinks &links);
};

QDataStream &operator <<(QDataStream &stream, const ProofLinks &links);
QDataStream &operator >>(QDataStream &stream, ProofLinks &links);
QDataStream &operator >>(QDataStream &stream, QVector<ProofLinks> &vec);

#endif // PROOFLINKS_H
