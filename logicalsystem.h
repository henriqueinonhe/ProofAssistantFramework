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
    LogicalSystem();

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QStringList getInferenceRulesPluginsNames() const;
    void setInferenceRulesPluginsNames(const QStringList &value);
    void addInferenceRulePluginName(const QString &pluginName);

    void loadInferenceRules();

    QString getInferenceRulesPluginsDirPath() const;
    void setInferenceRulesPluginsDirPath(const QString &value);

    QVector<InferenceRule *> getInferenceRules() const;

    Type getWffType() const;
    void setWffType(const Type &value);

protected:
    unique_ptr<const Type> wffType;
    QString name;
    QString description;
    QString inferenceRulesPluginsDirPath;
    QStringList inferenceRulesPluginsNames;
    QVector<InferenceRule *> inferenceRules; //I'm using raw pointers here because QPluginLoader already deletes
                                             //the plugin object when application terminates
};

#endif // LOGICALSYSTEM_H
