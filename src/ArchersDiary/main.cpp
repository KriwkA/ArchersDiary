#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QFile>
#include <QDir>

#include <tables/alltables.h>
#include <diarytables.h>
#include <QDebug>

#include "shottablemodel.h"

static const QString RS_IMAGES_PATH    = "img/images/";
static const QString RS_MENU_IMAGE     = RS_IMAGES_PATH + "menu.png";
static const QString RS_BACK_IMAGE     = RS_IMAGES_PATH + "back.png";
static const QString RS_FORWARD_IMAGE  = RS_IMAGES_PATH + "forward.png";
static const QString RS_ARCHER_IMAGE   = RS_IMAGES_PATH + "menu.png";
static const QString RS_ADD_IMAGE      = RS_IMAGES_PATH + "plus.png";
static const QString RS_REMOVE_IMAGE   = RS_IMAGES_PATH + "remove.png";
static const QString RS_EDIT_IMAGE     = RS_IMAGES_PATH + "edit.png";
static const QString RS_SETTINGS_IMAGE = RS_IMAGES_PATH + "settings.png";

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

void setTablesToContext(QQmlContext* context)
{
    context->setContextProperty("archersModel", (ArchersTableModel*)DiaryTables::getTableModel( TableType::Archrers ) );
    context->setContextProperty("arrowsModel", (ArrowsTableModel*)DiaryTables::getTableModel( TableType::Arrows ) );
    context->setContextProperty("bowsModel", (BowsTableModel*)DiaryTables::getTableModel( TableType::Bows ) );
    context->setContextProperty("scopesModel", (ScopesTableModel*)DiaryTables::getTableModel( TableType::Scopes ) );

    context->setContextProperty("trainingModel", (TrainingTableModel*)DiaryTables::getTableModel( TableType::Trainings ) );
    context->setContextProperty("recordModel", (RecordTableModel*)DiaryTables::getTableModel( TableType::Records ) );
    context->setContextProperty("trainingStandardModel", (TrainingStandardModel*)DiaryTables::getTableModel( TableType::TrainingStandards ) );
    context->setContextProperty("shotModel", (ShotModel*)DiaryTables::getTableModel( TableType::Shots ) );
    context->setContextProperty("simpleShotModel", (SimpleShotModel*)DiaryTables::getTableModel( TableType::SimpleShots ) );

    context->setContextProperty("standardModel", (StandardModel*)DiaryTables::getTableModel( TableType::Standards ) );
    context->setContextProperty("standardExcerciseModel", (StandardExcerciseModel*)DiaryTables::getTableModel( TableType::StandardExcersices ) );
    context->setContextProperty("excerciseModel", (ExcerciseModel*)DiaryTables::getTableModel( TableType::Excercises ) );
    context->setContextProperty("targetModel", (TargetModel*)DiaryTables::getTableModel( TableType::Targets ) );
}

void registerTypes()
{
    qmlRegisterType<ShotTableModel>("com.archersdiary.models", 1, 0, "ShotTableModel");
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
