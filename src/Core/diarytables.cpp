#include "precomp.h"
#include "tables/alltables.h"
#include "diarytables_p.h"
#include "diarytables.h"


DiaryTables::DiaryTables(QObject *parent)
    : QObject(parent)
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
    return nullptr;
}

RecordTableModel *DiaryTables::recordModel()
{
    return nullptr;
}

TrainingStandardModel *DiaryTables::trainingStandardModel()
{
    return nullptr;
}

StandardModel *DiaryTables::standardModel()
{
    return nullptr;
}

StandardExcersiceModel *DiaryTables::standardExcersiceModel()
{
    return nullptr;
}

ExcersiceModel *DiaryTables::excersiceModel()
{
    return nullptr;
}

ShotModel *DiaryTables::shotModel()
{
    return nullptr;
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
    return nullptr;
}

StandardExcersiceModel *DiaryTablesPrivate::initStandardExcersiceModel()
{
    return nullptr;
}

ExcersiceModel *DiaryTablesPrivate::initExcersiceModel()
{
    return nullptr;
}

TargetModel *DiaryTablesPrivate::initTargetModel()
{
    return nullptr;
}

ShotModel *DiaryTablesPrivate::initShotModel()
{
    return nullptr;
}

