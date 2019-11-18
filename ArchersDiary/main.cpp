#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QFile>
#include <QDir>

#include <tables/alltables.h>
#include <tables/dbtables.h>
#include <QDebug>

#include "shottablemodel.h"

namespace {

const QString RS_IMAGES_PATH    = "img/images/";
const QString RS_MENU_IMAGE     = RS_IMAGES_PATH + "menu.png";
const QString RS_BACK_IMAGE     = RS_IMAGES_PATH + "back.png";
const QString RS_FORWARD_IMAGE  = RS_IMAGES_PATH + "forward.png";
const QString RS_ARCHER_IMAGE   = RS_IMAGES_PATH + "menu.png";
const QString RS_ADD_IMAGE      = RS_IMAGES_PATH + "plus.png";
const QString RS_REMOVE_IMAGE   = RS_IMAGES_PATH + "remove.png";
const QString RS_EDIT_IMAGE     = RS_IMAGES_PATH + "edit.png";
const QString RS_SETTINGS_IMAGE = RS_IMAGES_PATH + "settings.png";

void setImagePathsToContext(QQmlContext* context)
{
    context->setContextProperty( "MenuImage", RS_MENU_IMAGE );
    context->setContextProperty( "BackImage", RS_BACK_IMAGE );
    context->setContextProperty( "ForwardImage", RS_FORWARD_IMAGE );
    context->setContextProperty( "ArcherImage", RS_ARCHER_IMAGE );
    context->setContextProperty( "AddImage", RS_ADD_IMAGE );
    context->setContextProperty( "RemoveImage", RS_REMOVE_IMAGE );
    context->setContextProperty( "EditImage", RS_EDIT_IMAGE );
    context->setContextProperty( "SettingsImage", RS_SETTINGS_IMAGE );
}

void setStylesToContext(QQmlContext* context)
{
    QQuickStyle::setStyle("Material");
    context->setContextProperty("availableStyles", QQuickStyle::availableStyles());
}


template<typename Table>
Table* TablePtr() {
    return &bl::db::DbTables::Instance().getTable<Table>();
}


void setTablesToContext(QQmlContext* context)
{
    context->setContextProperty("archersModel", TablePtr<ArchersTableModel>() );

    context->setContextProperty("trainingModel", TablePtr<TrainingTableModel>() );
    context->setContextProperty("recordModel", TablePtr<RecordTableModel>() );
    context->setContextProperty("trainingStandardModel", TablePtr<TrainingStandardModel>() );
    context->setContextProperty("shotModel", TablePtr<ShotModel>() );
    context->setContextProperty("simpleShotModel", TablePtr<SimpleShotModel>() );

    context->setContextProperty("standardModel", TablePtr<StandardModel>() );
    context->setContextProperty("standardExcerciseModel", TablePtr<StandardExcerciseModel>() );
    context->setContextProperty("excerciseModel", TablePtr<ExcerciseModel>() );
    context->setContextProperty("targetModel", TablePtr<TargetModel>() );
}

void registerTypes()
{
    qmlRegisterType<ShotTableModel>("com.archersdiary.models", 1, 0, "ShotTableModel");
}


}


int main(int argc, char *argv[])
{    
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    registerTypes();
    auto context = engine.rootContext();
    setImagePathsToContext( context );
    setStylesToContext( context );
    setTablesToContext( context );

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
