#ifndef LOGICALSYSTEM_H
#define LOGICALSYSTEM_H

#include <QString>
#include <memory>
#include "type.h"
#include "pluginwrapper.h"

typedef PluginWrapper<InferenceRule> InferenceRulePlugin;

using namespace std;

class LogicalSystem
{
public:
    LogicalSystem(const QString &name,
                  const QString &description,
                  QStringList inferenceRulesNamesList,
                  const QString &signatureName,
                  const Type &wffType);

    LogicalSystem(QDataStream &stream);

    void serialize(QDataStream &stream) const;

    QString getName() const;
    QString getDescription() const;
    QVector<InferenceRulePlugin> getInferenceRules() const;
    QString getSignatureName() const;
    Type getWffType() const;

protected:
    LogicalSystem();

    void setName(const QString &value);
    void setDescription(const QString &value);

    void loadInferenceRuleList(const QStringList &inferenceRulesNamesList);

    QString name;
    QString description;
    QVector<InferenceRulePlugin> inferenceRules;
    QString signatureName;
    unique_ptr<const Type> wffType;

    friend QDataStream &operator >>(QDataStream &stream, LogicalSystem &logicalSystem);
    friend QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);
    friend class ProgramManager;
};

QDataStream &operator >>(QDataStream &stream, LogicalSystem &logicalSystem);
QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);



#endif // LOGICALSYSTEM_H
