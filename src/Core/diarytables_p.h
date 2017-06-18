#ifndef MODELSWRAPPER_P_H
#define MODELSWRAPPER_P_H

#include <QScopedPointer>
#include <tables/alltables.h>

class DiaryTables;

class ArchersTableModel;
class ArrowsTableModel;
class BowsTableModel;
class ScopesTableModel;
class TrainingTableModel;
class RecordTableModel;
class TrainingStandardModel;
class StandardModel;
class StandardExcersiceModel;
class ExcersiceModel;
class TargetModel;
class ShotModel;

class DiaryTablesPrivate
{
    friend class DiaryTables;
    DiaryTables* q;

private:
    DiaryTablesPrivate(DiaryTables* qPtr);

    ArchersTableModel* initArchersTable();
    ArrowsTableModel* initArrowsTable();
    BowsTableModel* initBowsTable();
    ScopesTableModel* initScopesTableModel();


    TrainingTableModel* initTrainingModel();
    RecordTableModel* initRecordModel();
    TrainingStandardModel* initTrainingStandardModel();
    StandardModel* initStandardModel();
    StandardExcersiceModel* initStandardExcersiceModel();
    ExcersiceModel* initExcersiceModel();
    TargetModel* initTargetModel();
    ShotModel* initShotModel();


    template<typename Table>
    Q_ALWAYS_INLINE Table* initTable(Table* &dest)
    {
        if( dest != nullptr ) {
            return dest;
        }

        dest = new Table( m_db.data(), q );

        if( dest != nullptr ) {
            QString error;
            if( dest->init( error ) )
                return dest;

            qDebug() << error;
//            emit q->databaseError( error );
            delete dest;
        }                

        return dest = nullptr;
    }

    ArchersTableModel* m_archers = nullptr;
    ArrowsTableModel* m_arrows = nullptr;
    BowsTableModel* m_bows = nullptr;
    ScopesTableModel* m_scopes = nullptr;
    TrainingTableModel* m_trainings = nullptr;
    RecordTableModel* m_records = nullptr;
    TrainingStandardModel* m_trainingStandards = nullptr;
    StandardModel* m_standards = nullptr;
    StandardExcersiceModel* m_standardExcersices = nullptr;
    ExcersiceModel* m_excersices = nullptr;
    TargetModel* m_targets = nullptr;
    ShotModel* m_shots = nullptr;

    QScopedPointer< QSqlDatabase > m_db;

};





#endif // MODELSWRAPPER_P_H
