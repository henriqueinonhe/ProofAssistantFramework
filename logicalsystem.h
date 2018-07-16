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

    void loadInferenceRules();

    QString getInferenceRulesPluginsDirPath() const;
    void setInferenceRulesPluginsDirPath(const QString &value);

protected:
    QString name;
    QVector<Theory> theories;
    QString inferenceRulesPluginsDirPath;
    QStringList inferenceRulesPluginsNames;
    QVector<shared_ptr<InferenceRule>> inferenceRules;
};

#endif // LOGICALSYSTEM_H
