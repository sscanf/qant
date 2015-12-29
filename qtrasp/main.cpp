#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTime>
#include <QDebug>
#include <QQmlContext>
#include "listmodel.h"
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //1.96, 41.27
    //listModel model;
    //engine.rootContext()->setContextProperty("moonModel",&model);
    return app.exec();
}

