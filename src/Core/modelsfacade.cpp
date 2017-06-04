#include "modelsfacade.h"
#include "modelsfacade_p.h"

#include "database/sqltable.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>

ModelsFacade::ModelsFacade(QSqlDatabase *db, QObject *parent)
    : QObject(parent)
    , d(new ModelsFacaderPrivate(this, db))
{

}

QSqlTableModel *ModelsFacade::archersTable()
{
    return d->archersTable();
}

// PRIVATE

//const SqlTableRecord tblArchers = {
//    "Archers",
//    { "Id", "INTEGER", SqlField::PRIMARY_KEY },
//    { "Name", "TEXT" }
//};

ModelsFacaderPrivate::ModelsFacaderPrivate(ModelsFacade *qPtr, QSqlDatabase *db)
    : q( qPtr )
    , m_db( db )
    , m_archers( nullptr )
{

}

QSqlTableModel *ModelsFacaderPrivate::initArchersTable()
{
    if( m_archers != nullptr )
    {
        return m_archers;
    }
    return nullptr;
}

QSqlTableModel *ModelsFacaderPrivate::initTable(QSqlTableModel **tableModel, SqlTable &table)
{
    QString error;
    if( *tableModel != nullptr )
    {
        return *tableModel;
    }
    else if ( table.init(m_db, error) )
    {
        *tableModel = new QSqlTableModel( q, *m_db );
        (*tableModel)->setTable( table.name() );
        for(int i = 0; i < table.columns().size(); ++i)
        {
            (*tableModel)->setHeaderData( i, Qt::Horizontal, table.columns().at(i).name );
        }
    }
    return *tableModel;
}
