#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <diarytables.h>
#include <tables/archerstablemodel.h>
#include <tables/arrowstablemodel.h>
#include <QDebug>

void setStylesToContext(QQmlContext* context)
{
    QQuickStyle::setStyle("Material");
    context->setContextProperty("availableStyles", QQuickStyle::availableStyles());
}

void setTablesToContext(QQmlContext* context, DiaryTables& diary)
{
    context->setContextProperty("archersModel", diary.archersTableModel());
    context->setContextProperty("arrowsModel", diary.arrowsTableModel());
}

int main(int argc, char *argv[])
{    
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    DiaryTables diaryTables;

    QQmlApplicationEngine engine;

    setStylesToContext(engine.rootContext());
    setTablesToContext(engine.rootContext(), diaryTables);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
