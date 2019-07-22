#ifndef JUSTIFICATION_H
#define JUSTIFICATION_H

#include <QString>
#include <QStringList>

class Justification
{
public:
    Justification() = delete;
    Justification(const Justification &) = default;
    Justification(Justification &&) noexcept = default;
    Justification &operator =(const Justification &) = default;
    Justification &operator =(Justification &&) noexcept = default;
    ~Justification() noexcept = default;

    Justification(QDataStream &stream);
    Justification(const QString &inferenceRuleCallCommand, const QStringList &argumentList);

    bool operator==(const Justification &other) const;
    bool operator!=(const Justification &other) const;

    const QString &getInferenceRuleCallCommand() const;

    const QStringList &getArgumentList() const;

private:
    QString inferenceRuleCallCommand;
    QStringList argumentList;

    friend QDataStream &operator <<(QDataStream &stream, const Justification &justification);
    friend QDataStream &operator >>(QDataStream &stream, Justification &justification);
};

QDataStream &operator <<(QDataStream &stream, const Justification &justification);
QDataStream &operator >>(QDataStream &stream, Justification &justification);

#endif // JUSTIFICATION_H
