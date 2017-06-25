#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <tables/alltables.h>
#include <diarytables.h>
#include <QDebug>

void setStylesToContext(QQmlContext* context)
{
    QQuickStyle::setStyle("Material");
    context->setContextProperty("availableStyles", QQuickStyle::availableStyles());
}

void setTablesToContext(QQmlContext* context)
{
    auto diary = DiaryTables::getObject();
    context->setContextProperty("diaryTables", diary);
    context->setContextProperty("archersModel", diary->archersModel());
    context->setContextProperty("arrowsModel", diary->arrowsModel());
    context->setContextProperty("bowsModel", diary->bowsModel());
    context->setContextProperty("scopesModel", diary->scopesModel());

    context->setContextProperty("trainingModel", diary->trainingModel());
    context->setContextProperty("recordModel", diary->recordModel());
    context->setContextProperty("trainingStandardModel", diary->trainingStandardModel());
    context->setContextProperty("shotModel", diary->shotModel());

    context->setContextProperty("standardModel", diary->standardModel());
    context->setContextProperty("standardExcerciseModel", diary->standardExcersiceModel());
    context->setContextProperty("excerciseModel", diary->excersiceModel());
    context->setContextProperty("targetModel", diary->targetModel());

}

int main(int argc, char *argv[])
{    
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    setStylesToContext(engine.rootContext());
    setTablesToContext(engine.rootContext());

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
