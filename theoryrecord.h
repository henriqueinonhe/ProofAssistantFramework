#ifndef THEORYRECORD_H
#define THEORYRECORD_H

#include <QString>

struct TheoryRecord
{
public:
    TheoryRecord();
    TheoryRecord(const QString &name, const QString &description);

    const QString &getName() const;
    const QString &getDescription() const;

    QString name;
    QString description;

    friend QDataStream &operator <<(QDataStream &stream, const TheoryRecord &record);
    friend QDataStream &operator >>(QDataStream &stream, TheoryRecord &record);
};

QDataStream &operator <<(QDataStream &stream, const TheoryRecord &record);
QDataStream &operator >>(QDataStream &stream, TheoryRecord &record);

#endif // THEORYRECORD_H
