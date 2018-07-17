#ifndef JUSTIFICATION_H
#define JUSTIFICATION_H

#include <QString>
#include <QStringList>

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
};

#endif // JUSTIFICATION_H
