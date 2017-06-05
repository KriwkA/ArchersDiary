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

ArchersTableModel *DiaryTables::archersTableModel()
{
    QString error;
    auto archers = d->initArchersTable( error );
    if( archers != nullptr )
        return archers;
    emit databaseError( error );
    return nullptr;
}

// PRIVATE

DiaryTablesPrivate::DiaryTablesPrivate(DiaryTables *qPtr)
    : q( qPtr )
    , m_db( new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") ) )
    , m_archers( nullptr )
{
    m_db->setDatabaseName("db/archers.db");    
}

ArchersTableModel *DiaryTablesPrivate::initArchersTable(QString &error)
{
    if( m_archers != nullptr )
        return m_archers;

    QScopedPointer<ArchersTableModel> archers( new ArchersTableModel( m_db.data(), q ) );

    if( archers->init( error) )
        return m_archers = archers.take();

    return nullptr;
}

