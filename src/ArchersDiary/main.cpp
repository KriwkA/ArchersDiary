#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QFile>
#include <QDir>

#include <tables/alltables.h>
#include <diarytables.h>
#include <QDebug>

static const QString RS_IMAGES_PATH    = "img/images/";
static const QString RS_MENU_IMAGE     = RS_IMAGES_PATH + "menu.png";
static const QString RS_BACK_IMAGE     = RS_IMAGES_PATH + "back.png";
static const QString RS_ARCHER_IMAGE   = RS_IMAGES_PATH + "menu.png";
static const QString RS_ADD_IMAGE      = RS_IMAGES_PATH + "plus.png";
static const QString RS_REMOVE_IMAGE   = RS_IMAGES_PATH + "remove.png";
static const QString RS_EDIT_IMAGE     = RS_IMAGES_PATH + "edit.png";
static const QString RS_SETTINGS_IMAGE = RS_IMAGES_PATH + "settings.png";

void setImagePathsToContext(QQmlContext* context)
{
    context->setContextProperty( "MenuImage", RS_MENU_IMAGE );
    context->setContextProperty( "BackImage", RS_BACK_IMAGE );
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
    context->setContextProperty("archersModel", DiaryTables::getTableModel( TableType::Archrers ) );
    context->setContextProperty("arrowsModel", DiaryTables::getTableModel( TableType::Arrows ) );
    context->setContextProperty("bowsModel", DiaryTables::getTableModel( TableType::Bows ) );
    context->setContextProperty("scopesModel", DiaryTables::getTableModel( TableType::Scopes) );

    context->setContextProperty("trainingModel", DiaryTables::getTableModel( TableType::Trainings) );
    context->setContextProperty("recordModel", DiaryTables::getTableModel( TableType::Records) );
    context->setContextProperty("trainingStandardModel", DiaryTables::getTableModel( TableType::TrainingStandards) );
    context->setContextProperty("shotModel", DiaryTables::getTableModel( TableType::Shots) );

    context->setContextProperty("standardModel", DiaryTables::getTableModel( TableType::Standards ) );
    context->setContextProperty("standardExcerciseModel", DiaryTables::getTableModel( TableType::StandardExcersices ) );
    context->setContextProperty("excerciseModel", DiaryTables::getTableModel( TableType::Excercises ) );
    context->setContextProperty("targetModel", DiaryTables::getTableModel( TableType::Targets ) );
}

void registerTypes()
{
}

bool prepareDb()
{
    QFile db("diary.db");
    if( db.exists() )
        return true;

    QFile nullDb( ":/db/diary.db");
    if( nullDb.open( QFile::ReadOnly ) && db.open( QFile::WriteOnly ) )
    {
        db.write( nullDb.readAll() );
        db.close();
        nullDb.close();
        return true;
    }

    return false;
}

int main(int argc, char *argv[])
{    
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if( !prepareDb() )
        return -1;

    QQmlApplicationEngine engine;

    registerTypes();
    auto context = engine.rootContext();
    setImagePathsToContext( context );
    setStylesToContext( context );
    setTablesToContext( context );

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
