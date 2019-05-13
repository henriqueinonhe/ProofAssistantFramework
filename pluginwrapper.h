#ifndef PLUGINWRAPPER_H
#define PLUGINWRAPPER_H

#include <QPluginLoader>
#include <QDataStream>

template <class T> class PluginWrapper;
class InferenceRule;
class InferenceTactic;
template <class T> QDataStream &operator<<(QDataStream&, const PluginWrapper<T>&);
template <class T> QDataStream &operator>>(QDataStream&, PluginWrapper<T>&);

template<class T>
class PluginWrapper
{
public:
    PluginWrapper() : pluginPointer(nullptr)
    {}

    PluginWrapper(const QString &pluginPath) :
        pluginPath(pluginPath)
    {
        load(pluginPath);
    }

    PluginWrapper(const PluginWrapper &other)
    {
        *this = other;
    }

    PluginWrapper &operator=(const PluginWrapper &other)
    {
        this->pluginPath = other.pluginPath;
        this->pluginPointer = other.pluginPointer;
        this->loader.setFileName(other.loader.fileName());
        this->loader.load();

        return *this;
    }

    ~PluginWrapper()
    {
        loader.unload();
    }

    void load(const QString &pluginPath)
    {
        this->pluginPath = pluginPath;
        loader.setFileName(pluginPath);

        bool loadSuccess = loader.load();
        if(!loadSuccess)
        {
            QString errorMsg;
            errorMsg += "Couldn't load plugin named \"";
            errorMsg += pluginPath + "\".";
            throw std::runtime_error(errorMsg.toStdString());
        }

        pluginPointer = qobject_cast<T *>(loader.instance());
    }

    T *operator->()
    {
        if(!loader.isLoaded())
        {
            throw std::runtime_error("Plugin is not loaded yet!");
        }

        return pluginPointer;
    }

    T *ptr()
    {
        return pluginPointer;
    }

    template <class C> static void checkContainerPluginCollision(const C &container, const QString &pluginPath)
    {
        std::for_each(container.begin(), container.end(), [&](const PluginWrapper &plugin)
        {
            if(plugin.getPluginPath() == pluginPath)
            {
                QString errorMsg;
                errorMsg += "This plugin is already in use.";

                throw std::invalid_argument(errorMsg.toStdString());
            }
        });
    }

    template <class C> static void removePluginFromContainer(C &container, const QString &pluginPath)
    {
        for(auto iter = container.begin(); iter != container.end(); iter++)
        {
            if(iter->getPluginPath() == pluginPath)
            {
                container.erase(iter);
                return;
            }
        }

        throw std::invalid_argument("This plugin is not in the container!");
    }

    QString getPluginPath() const
    {
        return pluginPath;
    }

private:
    T *pluginPointer;
    QPluginLoader loader;
    QString pluginPath;

    friend QDataStream &operator<< <T>(QDataStream&, const PluginWrapper<T>&);
    friend QDataStream &operator>> <T>(QDataStream&, PluginWrapper<T>&);
};

template <class T>
QDataStream &operator<<(QDataStream &stream, const PluginWrapper<T> &plugin)
{
    stream << plugin.pluginPath;
    stream << *plugin.pluginPointer;
    return stream;
}

template <class T>
QDataStream &operator>>(QDataStream &stream, PluginWrapper<T> &plugin)
{
    stream >> plugin.pluginPath;
    plugin.load(plugin.pluginPath);
    stream >> *plugin.pluginPointer;
    return stream;
}

template <> inline
QDataStream &operator<< <InferenceRule>(QDataStream &stream, const PluginWrapper<InferenceRule> &plugin)
{
    stream << plugin.pluginPath;
    return stream;
}

template <> inline
QDataStream &operator>> <InferenceRule>(QDataStream &stream, PluginWrapper<InferenceRule> &plugin)
{
    stream >> plugin.pluginPath;
    plugin.load(plugin.pluginPath);
    return stream;
}

template <> inline
QDataStream &operator<< <InferenceTactic>(QDataStream &stream, const PluginWrapper<InferenceTactic> &plugin)
{
    stream << plugin.pluginPath;
    return stream;
}

template <> inline
QDataStream &operator>> <InferenceTactic>(QDataStream &stream, PluginWrapper<InferenceTactic> &plugin)
{
    stream >> plugin.pluginPath;
    plugin.load(plugin.pluginPath);
    return stream;
}

#endif // PLUGINWRAPPER_H
