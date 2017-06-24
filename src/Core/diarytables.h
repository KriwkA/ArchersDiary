#ifndef MODELSWRAPPER_H
#define MODELSWRAPPER_H

#include <core_global.h>
#include <QObject>

class DiaryTablesPrivate;

class ArchersTableModel;
class ArrowsTableModel;
class BowsTableModel;
class ScopesTableModel;
class TrainingTableModel;
class RecordTableModel;
class TrainingStandardModel;
class StandardModel;
class StandardExcerciseModel;
class ExcerciseModel;
class TargetModel;
class ShotModel;

class CORESHARED_EXPORT DiaryTables : public QObject
{
    Q_OBJECT
public:
    static DiaryTables* getObject();

    DiaryTables(DiaryTables&& move);
    void operator=(DiaryTables&& move);
    virtual ~DiaryTables();

    ArchersTableModel* archersModel();
    ArrowsTableModel* arrowsModel();
    BowsTableModel *bowsModel();
    ScopesTableModel *scopesModel();

    TrainingTableModel* trainingModel();
    RecordTableModel* recordModel();
    TrainingStandardModel* trainingStandardModel();
    StandardModel* standardModel();
    StandardExcerciseModel* standardExcersiceModel();
    ExcerciseModel* excersiceModel();
    TargetModel* targetModel();
    ShotModel* shotModel();

signals:
    void databaseError(QString error);

private:
    DiaryTables();

    Q_DISABLE_COPY( DiaryTables )
    friend class DiaryTablesPrivate;
    DiaryTablesPrivate* d;    
};




#endif // MODELSWRAPPER_H
