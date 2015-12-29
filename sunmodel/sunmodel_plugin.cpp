#include "sunmodel_plugin.h"
#include "sunmodel.h"

#include <qqml.h>

void SunmodelPlugin::registerTypes(const char *uri)
{
    // @uri com.mycompany.qmlcomponents
    qmlRegisterType<SunModel>(uri, 1, 0, "SunModel");
}


