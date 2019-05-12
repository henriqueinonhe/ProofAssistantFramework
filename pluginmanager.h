#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QPluginLoader>
#include <QVector>
#include "storagemanager.h"

class PluginManager
{
public:
    PluginManager();



    template<class T>
    static void serializePluginVector(QDataStream &stream, const QVector<T *> &pluginVector)
    {
        std::for_each(pluginVector.begin(), pluginVector.end(), [&stream](const T * const plugin)
        {
            stream << *plugin;
        });
    }

    template<class T>
    static void unserializePluginVector(QDataStream &stream, QVector<T *> &pluginVector)
    {
        std::for_each(pluginVector.begin(), pluginVector.end(), [&stream](T * const plugin)
        {
            stream >> *plugin;
        });
    }

    template<class T>
    static void loadSinglePlugin(T* &plugin, const QString &pluginName, QString pluginPathFunction(const QString &))
    {
        QPluginLoader loader;
        loader.setFileName(pluginPathFunction(pluginName));

        bool loadSuccess = loader.load();
        if(!loadSuccess)
        {
            QString errorMsg;
            errorMsg += "Couldn't load plugin named \"";
            errorMsg += pluginPathFunction(pluginName) + "\".";
            throw std::runtime_error(errorMsg.toStdString());
        }

        plugin = qobject_cast<T *>(loader.instance());
    }

    template<class T>
    static void loadPluginVector(QVector<T *> &pluginVector, const QStringList &pluginsNameList, QString pluginPathFunction(const QString &))
    {
        std::for_each(pluginsNameList.begin(), pluginsNameList.end(), [&pluginVector, &pluginPathFunction] (const QString &pluginName)
        {
            T *plugin;
            PluginManager::loadSinglePlugin<T>(plugin, pluginName, pluginPathFunction);

            pluginVector.push_back(plugin);
        });
    }

};

#endif // PLUGINMANAGER_H
