#ifndef JUSTIFICATION_H
#define JUSTIFICATION_H

#include <QString>
#include <QStringList>

class Justification
{
public:
    Justification(QDataStream &stream);
    Justification(const QString &inferenceRuleCallCommand, const QStringList &argumentList);

    bool operator==(const Justification &other) const;
    bool operator!=(const Justification &other) const;

    QString getInferenceRuleCallCommand() const;

    QStringList getArgumentList() const;

private:
    Justification();

    QString inferenceRuleCallCommand;
    QStringList argumentList;

    friend class LineOfProof;
    friend QDataStream &operator <<(QDataStream &stream, const Justification &justification);
    friend QDataStream &operator >>(QDataStream &stream, Justification &justification);
};

QDataStream &operator <<(QDataStream &stream, const Justification &justification);
QDataStream &operator >>(QDataStream &stream, Justification &justification);

#endif // JUSTIFICATION_H
