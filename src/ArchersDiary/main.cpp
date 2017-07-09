#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QFile>
#include <QDir>

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
    setStylesToContext(engine.rootContext());
    setTablesToContext(engine.rootContext());

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
