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
    QString error;
    auto archers = d->initArchersTable( error );
    if( archers != nullptr )
        return archers;
    emit databaseError( error );
    return nullptr;
}

ArrowsTableModel *DiaryTables::arrowsTableModel()
{
    QString error;
    auto arrows = d->initArrowsTable( error );
    if( arrows != nullptr )
        return arrows;
    emit databaseError( error );
    return nullptr;
}

// PRIVATE

DiaryTablesPrivate::DiaryTablesPrivate(DiaryTables *qPtr)
    : q( qPtr )
    , m_db( new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") ) )
    , m_archers( nullptr )
    , m_arrows( nullptr )
{
    m_db->setDatabaseName("diary.db");
}

ArchersTableModel *DiaryTablesPrivate::initArchersTable(QString &error)
{
    if( m_archers != nullptr )
        return m_archers;

    QScopedPointer<ArchersTableModel> archers( new ArchersTableModel( m_db.data(), q ) );

    if( archers->init( error ) )
        return m_archers = archers.take();

    return nullptr;
}

ArrowsTableModel *DiaryTablesPrivate::initArrowsTable(QString &error)
{
    if( m_arrows != nullptr )
        return m_arrows;

    QScopedPointer<ArrowsTableModel> arrows( new ArrowsTableModel( m_db.data(), q ) );

    if( arrows->init( error ) )
        return m_arrows = arrows.take();

    return nullptr;
}

