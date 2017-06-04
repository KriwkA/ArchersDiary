#include "diarytables.h"
#include "diarytables_p.h"

#include "tables/archerstablemodel.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>

DiaryTables::DiaryTables(QObject *parent)
    : QObject(parent)
    , d(new DiaryTablesPrivate(this))
{
}

SqlTableModel *DiaryTables::archersTableModel(QString &error)
{
    return d->initArchersTable( error );
}

// PRIVATE

DiaryTablesPrivate::DiaryTablesPrivate(DiaryTables *qPtr)
    : q( qPtr )
    , m_db( new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") ) )
    , m_archers( nullptr )
{
    m_db->setDatabaseName("db/archers.db");    
}

SqlTableModel *DiaryTablesPrivate::initArchersTable(QString &error)
{
    if( m_archers != nullptr )
        return m_archers;

    QScopedPointer<ArchersTableModel> archers( new ArchersTableModel( m_db.data(), q ) );

    if( archers->init( error) )
        return m_archers = archers.take();

    return nullptr;
}

