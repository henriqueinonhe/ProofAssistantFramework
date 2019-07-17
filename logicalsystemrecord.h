#ifndef LOGICALSYSTEMRECORD_H
#define LOGICALSYSTEMRECORD_H

#include <QString>

struct LogicalSystemRecord
{
public:
    LogicalSystemRecord();
    LogicalSystemRecord(const QString &name, const QString &description);

    const QString &getName() const;
    const QString &getDescription() const;

    QString name;
    QString description;

    friend QDataStream &operator <<(QDataStream &stream, const LogicalSystemRecord &record);
    friend QDataStream &operator >>(QDataStream &stream, LogicalSystemRecord &record);
};

QDataStream &operator <<(QDataStream &stream, const LogicalSystemRecord &record);
QDataStream &operator >>(QDataStream &stream, LogicalSystemRecord &record);

#endif // LOGICALSYSTEMRECORD_H
