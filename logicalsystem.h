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
    LogicalSystem() = delete; //NOTE Maybe this is being used somewhere
    LogicalSystem(const LogicalSystem &) = delete;
    LogicalSystem(LogicalSystem &&) noexcept = default;
    LogicalSystem &operator =(const LogicalSystem &) = delete;
    LogicalSystem &operator =(const LogicalSystem &&) = delete;
    ~LogicalSystem() noexcept = default;

    LogicalSystem(const QString &name,
                  const QString &description,
                  const QVector<shared_ptr<const InferenceRule>> &inferenceRules,
                  const Type &wffType);

    LogicalSystem(QDataStream &stream, const QVector<shared_ptr<const InferenceRule>> &inferenceRules);

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
    Type wffType;

    friend QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);
    friend class ProgramManager;
};

QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);



#endif // LOGICALSYSTEM_H
