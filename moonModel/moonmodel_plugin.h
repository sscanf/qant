#ifndef MoonModel_PLUGIN_H
#define MoonModel_PLUGIN_H

#include <QQmlExtensionPlugin>

class MoonModelPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // MoonModel_PLUGIN_H

