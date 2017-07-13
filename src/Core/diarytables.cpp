#include "precomp.h"
#include "tables/alltables.h"
#include "diarytables.h"
#include "diarytables_p.h"
#include "exception"

DiaryTables::DiaryTables()
    : QObject( nullptr )
    , d( new DiaryTablesPrivate( this ) )
{    
}

DiaryTables *DiaryTables::getObject()
{
    static DiaryTables* object = nullptr;
    if( object == nullptr )
        object = new DiaryTables();
    return object;
}

DiaryTables::~DiaryTables()
{
    delete d;
}

SqlTableModel *DiaryTables::getTableModel( TableType tableType )
{
    DiaryTables* instance = getObject();
    if( instance != nullptr ) {
        return instance->d->initTable( tableType );
    }
    return nullptr;
}

// PRIVATE

DiaryTablesPrivate::DiaryTablesPrivate(DiaryTables *qPtr)
    : q( qPtr )
    , m_db( new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") ) )
{
    m_db->setDatabaseName("diary.db");
    if(m_db->open()) {
        QSqlQuery query(*m_db);
        if( query.exec("PRAGMA foreign_keys = ON;") ) {
            return;
        }
        throw std::runtime_error( "Data base: foreing keys wasn`t on" );
    }
    throw std::runtime_error( "Data base: db not opened" );
}

SqlTableModel *DiaryTablesPrivate::initTable( TableType tableType )
{
    switch ( tableType ) {
        case TableType::Archrers:           return initTable( m_archers );
        case TableType::Arrows:             return initTable( m_arrows );
        case TableType::Bows:               return initTable( m_bows );
        case TableType::Scopes:             return initTable( m_scopes );
        case TableType::Trainings:          return initTable( m_trainings );
        case TableType::Records:            return initTable( m_records );
        case TableType::Standards:          return initTable( m_standards );
        case TableType::Targets:            return initTable( m_targets );
        case TableType::Excercises:         return initTable( m_excersices );
        case TableType::StandardExcersices: return initTable( m_standardExcersices );
        case TableType::TrainingStandards:  return initTable( m_trainingStandards );
        case TableType::Shots:              return initTable( m_shots );
        case TableType::SimpleShot:         return initTable( m_simpleShots );
    }
    return nullptr;
}

template<typename TablePtr>
Q_ALWAYS_INLINE SqlTableModel *DiaryTablesPrivate::initTable(TablePtr *&dest)
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

