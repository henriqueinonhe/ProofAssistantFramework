#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "pluginfactoryinterface.h"
#include <QString>
#include <QPluginLoader>
#include <memory>

using namespace std;

class PluginManager
{
public:
    template <class T> static shared_ptr<T> fetchPlugin(const QString &pluginPath)
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

        PluginFactoryInterface<T> *factory = qobject_cast<PluginFactoryInterface<T> *>(loader.instance());
        return factory->instance();
    }

    template <class T> static QVector<shared_ptr<T>> fetchPluginVector(const QStringList &pluginPathList)
    {
        QVector<shared_ptr<T>> vec;
        std::for_each(pluginPathList.begin(), pluginPathList.end(), [&vec](const QString &pluginPath)
        {
            shared_ptr<T> ptr = fetchPlugin<T>(pluginPath);
            vec.push_back(ptr);
        });

        return vec;
    }

};

#endif // PLUGINMANAGER_H
