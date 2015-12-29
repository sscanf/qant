#include "moonmodel_plugin.h"
#include "moonmodel.h"

#include <qqml.h>

void MoonModelPlugin::registerTypes(const char *uri)
{
    // @uri com.mycompany.qmlcomponents
    qmlRegisterType<MoonModel>(uri, 1, 0, "MoonModel");
}
