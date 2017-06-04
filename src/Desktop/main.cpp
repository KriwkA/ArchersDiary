#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <modelsfacade.h>
#include <database/sqltable.h>
#include <QSqlDatabase>
#include <QSqlTableModel>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("achresdiary.db");
    ModelsFacade diariesTables(&db);

    QString error;

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    ModelsFacade::archersTable().insertValues(&db, QVariantList() << "aaa", error);

    auto archerTableModel = diariesTables.archersTableModel(error);
    archerTableModel->select();

    context->setContextProperty("ArchersModel", (QObject*)archerTableModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
