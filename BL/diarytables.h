#pragma once
#include <bl_global.h>
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

class BL_SHARED_EXPORT DiaryTables : public QObject
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
