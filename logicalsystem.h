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
                  const Type &wffType);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QVector<InferenceRule *> getInferenceRules() const;

    Type getWffType() const;
    void setWffType(const Type &value);

protected:
    QString name;
    QString description;
    QVector<InferenceRule *> inferenceRules; //Does not own inference rules, thus they must be owned by an external object
    unique_ptr<const Type> wffType;

    friend QDataStream &operator <<(QDataStream &stream, const LogicalSystem &system);
    friend QDataStream &operator >>(QDataStream &stream, LogicalSystem &system);
};

QDataStream &operator <<(QDataStream &stream, const LogicalSystem &system);
QDataStream &operator >>(QDataStream &stream, LogicalSystem &system);

#endif // LOGICALSYSTEM_H
