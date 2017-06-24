#include "precomp.h"
#include "tables/alltables.h"
#include "diarytables.h"
#include "diarytables_p.h"

DiaryTables::DiaryTables()
    : QObject( nullptr )
    , d(new DiaryTablesPrivate(this))
{    
}

DiaryTables::DiaryTables(DiaryTables &&move)
    : QObject(move.parent())
    , d(move.d)
{
    d->q = this;
    move.d = new DiaryTablesPrivate(&move);
}

DiaryTables *DiaryTables::getObject()
{
    static DiaryTables* object = nullptr;
    if( object == nullptr )
        object = new DiaryTables();
    return object;
}

void DiaryTables::operator=(DiaryTables &&move)
{
    if(this != &move) {
        setParent(move.parent());
        d = move.d;
        d->q = this;
        move.d = new DiaryTablesPrivate(&move);
    }
}

DiaryTables::~DiaryTables()
{
    delete d;
}

ArchersTableModel *DiaryTables::archersModel()
{    
    return d->initArchersTable();
}

ArrowsTableModel *DiaryTables::arrowsModel()
{    
    return d->initArrowsTable();
}

BowsTableModel *DiaryTables::bowsModel()
{
    return d->initBowsTable();
}

ScopesTableModel *DiaryTables::scopesModel()
{
    return d->initScopesTableModel();
}

TrainingTableModel *DiaryTables::trainingModel()
{
    return d->initTrainingModel();
}

RecordTableModel *DiaryTables::recordModel()
{
    return d->initRecordModel();
}

TrainingStandardModel *DiaryTables::trainingStandardModel()
{
    return d->initTrainingStandardModel();
}

StandardModel *DiaryTables::standardModel()
{
    return d->initStandardModel();
}

StandardExcerciseModel *DiaryTables::standardExcersiceModel()
{
    return d->initStandardExcersiceModel();
}

ExcerciseModel *DiaryTables::excersiceModel()
{
    return d->initExcersiceModel();
}

TargetModel *DiaryTables::targetModel()
{
    return d->initTargetModel();
}

ShotModel *DiaryTables::shotModel()
{
    return d->initShotModel();
}

// PRIVATE

DiaryTablesPrivate::DiaryTablesPrivate(DiaryTables *qPtr)
    : q( qPtr )
    , m_db( new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") ) )
{
    m_db->setDatabaseName("diary.db");
    if(m_db->open())
    {
        QSqlQuery query(*m_db);
        if(query.exec("PRAGMA foreign_keys = ON;")) {
            return;
        }
    }
    throw;
}

ArchersTableModel *DiaryTablesPrivate::initArchersTable()
{        
    return initTable( m_archers );
}

ArrowsTableModel *DiaryTablesPrivate::initArrowsTable()
{
    return initTable( m_arrows );
}

BowsTableModel *DiaryTablesPrivate::initBowsTable()
{
    return initTable( m_bows );
}

ScopesTableModel *DiaryTablesPrivate::initScopesTableModel()
{
    return initTable( m_scopes );
}

TrainingTableModel *DiaryTablesPrivate::initTrainingModel()
{
    return initTable( m_trainings );
}

RecordTableModel *DiaryTablesPrivate::initRecordModel()
{
    return initTable( m_records );
}

TrainingStandardModel *DiaryTablesPrivate::initTrainingStandardModel()
{
    return nullptr;
}

StandardModel *DiaryTablesPrivate::initStandardModel()
{
    return initTable( m_standards );
}

StandardExcerciseModel *DiaryTablesPrivate::initStandardExcersiceModel()
{
    return initTable( m_standardExcersices );
}

ExcerciseModel *DiaryTablesPrivate::initExcersiceModel()
{
    return initTable( m_excersices );
}

TargetModel *DiaryTablesPrivate::initTargetModel()
{
    return initTable( m_targets );
}

ShotModel *DiaryTablesPrivate::initShotModel()
{
    return nullptr;
}

