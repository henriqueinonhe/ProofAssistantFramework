#ifndef LOGICALSYSTEM_H
#define LOGICALSYSTEM_H

#include <QString>
#include <memory>
#include "type.h"
#include "inferencerule.h"

using namespace std;

class LogicalSystem
{
public:
    LogicalSystem(const QString &name,
                  const QString &description,
                  const QVector<const InferenceRule *> &inferenceRules,
                  const Type &wffType);

    LogicalSystem(QDataStream &stream, const QVector<const InferenceRule *> &inferenceRules);

    QString getName() const;
    QString getDescription() const;
    QVector<shared_ptr<const InferenceRule>> getInferenceRules() const;
    Type getWffType() const;

protected:
    void setName(const QString &value);
    void setDescription(const QString &value);

    QString name;
    QString description;
    QVector<shared_ptr<const InferenceRule>> inferenceRules;
    unique_ptr<const Type> wffType;

    friend QDataStream &operator >>(QDataStream &stream, LogicalSystem &logicalSystem);
    friend QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);
    friend class ProgramManager;
};

QDataStream &operator >>(QDataStream &stream, LogicalSystem &logicalSystem);
QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);



#endif // LOGICALSYSTEM_H
