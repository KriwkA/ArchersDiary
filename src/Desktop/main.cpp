#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <diarytables.h>
#include <tables/archerstablemodel.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    QString error;

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();

    DiaryTables diariesTables;


    auto archerTableModel = (ArchersTableModel*)diariesTables.archersTableModel(error);    
    archerTableModel->select();


    context->setContextProperty("ArchersModel", (QObject*)archerTableModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
