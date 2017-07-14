#ifndef MODELSWRAPPER_H
#define MODELSWRAPPER_H

#include <core_global.h>
#include <QObject>

class DiaryTablesPrivate;
class SqlTableModel;

enum class TableType
{
    Archrers,
    Arrows,
    Bows,
    Scopes,
    Trainings,
    Records,
    Standards,
    Targets,
    Excercises,
    StandardExcersices,
    TrainingStandards,
    Shots,
    SimpleShots
};

class CORESHARED_EXPORT DiaryTables : public QObject
{
    Q_OBJECT
public:
    virtual ~DiaryTables();

    static SqlTableModel* getTableModel( TableType tableType );

signals:
    void databaseError(QString error);

private:
    DiaryTables();
    static DiaryTables* getObject();

    Q_DISABLE_COPY( DiaryTables )
    friend class DiaryTablesPrivate;
    DiaryTablesPrivate* d;    
};




#endif // MODELSWRAPPER_H
