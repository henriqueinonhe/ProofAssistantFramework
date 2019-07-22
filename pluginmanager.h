#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "pluginfactoryinterface.h"
#include <QString>
#include <QPluginLoader>
#include <memory>
#include "lineofproofsectionmanager.h"
#include <QDataStream>
#include "proof.h"

using namespace std;

class PluginManager
{
public:
    static const QString defaultProofPluginName;

    template <class T> static shared_ptr<T> fetchPlugin(const QString &pluginPath)
    {
        const auto factory = fetchPluginFactory<T>(pluginPath);
        return factory->instance();
    }

    template <class T> static shared_ptr<T> fetchPlugin(const QString &pluginPath, QDataStream &stream)
    {
        const auto factory = fetchPluginFactory<T>(pluginPath);
        return factory->instance(stream);
    }

    static shared_ptr<Proof> fetchPlugin(const QString &pluginPath,
                                         const uint id,
                                         const QString &name,
                                         const QString &description,
                                         const QVector<Formula> &premises,
                                         const Formula &conclusion)
    {
        const auto factory = fetchPluginFactory<Proof>(pluginPath);
        return factory->instance(id, name, description, premises, conclusion);
    }


    template <class T> static QVector<shared_ptr<T>> fetchPluginVector(const QStringList &pluginPathList)
    {
        QVector<shared_ptr<T>> vec;
        for(const auto &pluginPath : pluginPathList)
        {
            auto ptr = fetchPlugin<T>(pluginPath);
            vec.push_back(ptr);
        }

        return vec;
    }

private:
    template <class T> static PluginFactoryInterface<T> *fetchPluginFactory(const QString &pluginPath)
    {
        //NOTE Maybe I should unload the loader!
        QPluginLoader loader(pluginPath);
        if(!loader.load())
        {
            QString errorMsg;
            errorMsg += "The plugin at \"";
            errorMsg += pluginPath;
            errorMsg += "\" couldn't be loaded!";
            throw std::invalid_argument(errorMsg.toStdString());
        }

        return qobject_cast<PluginFactoryInterface<T> *>(loader.instance());
    }

};

#endif // PLUGINMANAGER_H
