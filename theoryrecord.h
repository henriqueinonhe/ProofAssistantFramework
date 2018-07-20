#ifndef THEORYRECORD_H
#define THEORYRECORD_H

#include <QString>
#include <QDataStream>

class TheoryRecord
{
public:
    TheoryRecord();
    TheoryRecord(const QString &name, const QString &description);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

private:
    QString name;
    QString description;

    friend QDataStream &operator <<(QDataStream &stream, const TheoryRecord &record);
    friend QDataStream &operator >>(QDataStream &stream, TheoryRecord &record);
};

QDataStream &operator <<(QDataStream &stream, const TheoryRecord &record);
QDataStream &operator >>(QDataStream &stream, TheoryRecord &record);

#endif // THEORYRECORD_H
