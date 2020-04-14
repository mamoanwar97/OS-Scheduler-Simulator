#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include<bits/stdc++.h>
#include "scheduler.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    Scheduler* scheduler=new Scheduler;
    engine.rootContext()->setContextProperty("Scheduler",scheduler);

    return app.exec();
}
