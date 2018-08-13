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
#include "storagemanager.h"
#include "pluginmanager.h"

using namespace std;

class LogicalSystem
{
public:
    LogicalSystem();
    LogicalSystem(const QString &name,
                  const QString &description,
                  const QVector<const InferenceRule *> inferenceRules,
                  const Type &wffType);

    LogicalSystem(QDataStream &stream, QVector<const InferenceRule *> &inferenceRules);

    void serialize(QDataStream &stream) const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QVector<const InferenceRule *> getInferenceRules() const;

    Type getWffType() const;

protected:
    QString name;
    QString description;
    QVector<const InferenceRule *> inferenceRules; //Does not own inference rules, must be owned by somebody else
    unique_ptr<const Type> wffType;

    friend QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);
};

QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem);


#endif // LOGICALSYSTEM_H
