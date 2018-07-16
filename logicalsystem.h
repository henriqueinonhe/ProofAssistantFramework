#ifndef LOGICALSYSTEM_H
#define LOGICALSYSTEM_H

#include <QString>
#include "parser.h"
#include <memory>
#include "theory.h"
#include "inferencerule.h"
#include <QPluginLoader>

using namespace std;

class LogicalSystem
{
public:
    LogicalSystem();

    QString getName() const;
    void setName(const QString &value);


    QStringList getInferenceRulesPluginsNames() const;
    void setInferenceRulesPluginsNames(const QStringList &value);
    void addInferenceRulePluginName(const QString &pluginName);

    void loadInferenceRules();

    QString getInferenceRulesPluginsDirPath() const;
    void setInferenceRulesPluginsDirPath(const QString &value);

    QVector<InferenceRule *> getInferenceRules() const;

protected:
    QString name;
    QVector<Theory> theories;
    QString inferenceRulesPluginsDirPath;
    QStringList inferenceRulesPluginsNames;
    QVector<InferenceRule *> inferenceRules; //I'm using raw pointers here because QPluginLoader already deletes
                                             //the plugin object when application terminates
};

#endif // LOGICALSYSTEM_H
