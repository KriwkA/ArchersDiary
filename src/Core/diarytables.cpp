#include "diarytables.h"
#include "diarytables_p.h"

#include "tables/archerstablemodel.h"
#include "tables/arrowstablemodel.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>

DiaryTables::DiaryTables(QObject *parent)
    : QObject(parent)
    , d(new DiaryTablesPrivate(this))
{
}

ArchersTableModel *DiaryTables::archersTableModel()
{    
    return d->initArchersTable();
}

ArrowsTableModel *DiaryTables::arrowsTableModel()
{    
    return d->initArrowsTable();
}

ArrowsTableModel *DiaryTables::bowsTableModel()
{
    return nullptr;
}

ArrowsTableModel *DiaryTables::scopesTableModel()
{
    return nullptr;
}

// PRIVATE

DiaryTablesPrivate::DiaryTablesPrivate(DiaryTables *qPtr)
    : q( qPtr )
    , m_archers( nullptr )
    , m_arrows( nullptr )
    , m_db( new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") ) )
{
    m_db->setDatabaseName("diary.db");
}

ArchersTableModel *DiaryTablesPrivate::initArchersTable()
{    
    return (ArchersTableModel*)initTable(new ArchersTableModel( m_db.data(), q ), (SqlTableModel**)(&m_archers) );
}

ArrowsTableModel *DiaryTablesPrivate::initArrowsTable()
{
    return (ArrowsTableModel*)initTable(new ArrowsTableModel( m_db.data(), q ), (SqlTableModel**)(&m_arrows) );
}

SqlTableModel *DiaryTablesPrivate::initTable(SqlTableModel* table, SqlTableModel **dest)
{
    if( *dest != nullptr ) {
        if(*dest != table)
            delete table;
        return *dest;
    }

    QString error;
    if( table->init( error ) )
        return *dest = table;
    emit q->databaseError( error );

    delete table;

    return nullptr;
}

