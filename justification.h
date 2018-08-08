#ifndef JUSTIFICATION_H
#define JUSTIFICATION_H

#include <QString>
#include <QStringList>
#include <QDataStream>

class Justification
{
public:
    Justification();
    Justification(const QString &inferenceRuleCallCommand, const QStringList &argumentList);

    QString getInferenceRuleCallCommand() const;
    void setInferenceRuleCallCommand(const QString &value);

    QStringList getArgumentList() const;
    void setArgumentList(const QStringList &value);

private:
    QString inferenceRuleCallCommand;
    QStringList argumentList;

    friend QDataStream &operator <<(QDataStream &stream, const Justification &justification);
    friend QDataStream &operator >>(QDataStream &stream, Justification &justification);
};

QDataStream &operator <<(QDataStream &stream, const Justification &justification);
QDataStream &operator >>(QDataStream &stream, Justification &justification);

#endif // JUSTIFICATION_H
