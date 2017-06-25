#include "precomp.h"
#include "tables/alltables.h"
#include "diarytables.h"
#include "diarytables_p.h"

DiaryTables::DiaryTables()
    : QObject( nullptr )
    , d( new DiaryTablesPrivate( this ) )
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

Q_ALWAYS_INLINE ArchersTableModel *DiaryTablesPrivate::initArchersTable()
{        
    return initTable( m_archers );
}

Q_ALWAYS_INLINE ArrowsTableModel *DiaryTablesPrivate::initArrowsTable()
{
    return initTable( m_arrows );
}

Q_ALWAYS_INLINE BowsTableModel *DiaryTablesPrivate::initBowsTable()
{
    return initTable( m_bows );
}

Q_ALWAYS_INLINE ScopesTableModel *DiaryTablesPrivate::initScopesTableModel()
{
    return initTable( m_scopes );
}

Q_ALWAYS_INLINE TrainingTableModel *DiaryTablesPrivate::initTrainingModel()
{
    return initTable( m_trainings );
}

Q_ALWAYS_INLINE RecordTableModel *DiaryTablesPrivate::initRecordModel()
{
    return initTable( m_records );
}

Q_ALWAYS_INLINE TrainingStandardModel *DiaryTablesPrivate::initTrainingStandardModel()
{
    return initTable( m_trainingStandards );
}

Q_ALWAYS_INLINE StandardModel *DiaryTablesPrivate::initStandardModel()
{
    return initTable( m_standards );
}

Q_ALWAYS_INLINE StandardExcerciseModel *DiaryTablesPrivate::initStandardExcersiceModel()
{
    return initTable( m_standardExcersices );
}

Q_ALWAYS_INLINE ExcerciseModel *DiaryTablesPrivate::initExcersiceModel()
{
    return initTable( m_excersices );
}

Q_ALWAYS_INLINE TargetModel *DiaryTablesPrivate::initTargetModel()
{
    return initTable( m_targets );
}

Q_ALWAYS_INLINE ShotModel *DiaryTablesPrivate::initShotModel()
{
    return initTable( m_shots );
}

template<typename TablePtr>
Q_ALWAYS_INLINE TablePtr *DiaryTablesPrivate::initTable(TablePtr *&dest)
{
    if( dest != nullptr ) {
        return dest;
    }

    dest = new TablePtr( m_db.data(), q );

    if( dest != nullptr ) {
        QString error;
        if( dest->init( error ) )
            return dest;
        emit q->databaseError( error );
        delete dest;
    }

    return dest = nullptr;
}

