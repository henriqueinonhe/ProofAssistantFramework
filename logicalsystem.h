#ifndef LOGICALSYSTEM_H
#define LOGICALSYSTEM_H

#include <QString>
#include "parser.h"
#include <memory>
#include "theory.h"
#include "inferencerule.h"
#include <QPluginLoader>
#include "type.h"
#include <QFile>
#include <QDataStream>

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

    QVector<InferenceRule *> getInferenceRules() const;

    Type getWffType() const;

    QString getSignatureName() const;

protected:
    LogicalSystem();

    void setName(const QString &value);
    void setDescription(const QString &value);

    void loadInferenceRuleList();

    QString name;
    QString description;
    QStringList inferenceRulesNamesList;
    QVector<InferenceRule *> inferenceRules; //Does not own inference rules, must be owned by somebody else, most likely by the plugin loader
    QString signatureName;
    unique_ptr<const Type> wffType;

    friend QDataStream &operator >>(QDataStream &stream, LogicalSystem &logicalSystem);
    friend QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);
    friend class ProgramManager;
};

QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);


#endif // LOGICALSYSTEM_H
