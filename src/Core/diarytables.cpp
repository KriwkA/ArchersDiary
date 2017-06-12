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

ArchersTableModel *DiaryTables::archersTableModel()
{    
    return d->initArchersTable();
}

ArrowsTableModel *DiaryTables::arrowsTableModel()
{    
    return d->initArrowsTable();
}

BowsTableModel *DiaryTables::bowsTableModel()
{
    return d->initBowsTable();
}

ScopesTableModel *DiaryTables::scopesTableModel()
{
    return d->initScopesTableModel();
}

// PRIVATE

DiaryTablesPrivate::DiaryTablesPrivate(DiaryTables *qPtr)
    : q( qPtr )
    , m_archers( nullptr )
    , m_arrows( nullptr )
    , m_bows( nullptr )
    , m_scopes( nullptr )
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

