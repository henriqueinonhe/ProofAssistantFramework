#ifndef LOGICALSYSTEMRECORD_H
#define LOGICALSYSTEMRECORD_H

#include <QString>
#include <QDataStream>

class LogicalSystemRecord
{
public:
    LogicalSystemRecord();
    LogicalSystemRecord(const QString &name, const QString &description);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

private:
    QString name;
    QString description;

    friend QDataStream &operator <<(QDataStream &stream, const LogicalSystemRecord &record);
    friend QDataStream &operator >>(QDataStream &stream, LogicalSystemRecord &record);
};

QDataStream &operator <<(QDataStream &stream, const LogicalSystemRecord &record);
QDataStream &operator >>(QDataStream &stream, LogicalSystemRecord &record);

#endif // LOGICALSYSTEMRECORD_H
