#include "modelsfacade.h"
#include "modelsfacade_p.h"

#include "database/sqltable.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>

ModelsFacade::ModelsFacade(QSqlDatabase *db, QObject *parent)
    : QObject(parent)
    , d(new ModelsFacadePrivate(this, db))
{

}

SqlTable ModelsFacade::archersTable()
{
    SqlTable::SqlColumn id;
    id.name = "Id";
    id.dataType = "INTEGER";
    id.type = SqlTable::PRIMARY_KEY;

    SqlTable::SqlColumn name;
    name.name = "Name";
    name.dataType = "TEXT";

    return SqlTable("Archers", { id, name });
}

QSqlTableModel *ModelsFacade::archersTableModel(QString &error)
{
    return d->archersTable(error);
}

// PRIVATE

ModelsFacadePrivate::ModelsFacadePrivate(ModelsFacade *qPtr, QSqlDatabase *db)
    : q( qPtr )
    , m_db( db )
    , m_archers( nullptr )
{

}

QSqlTableModel *ModelsFacadePrivate::initArchersTable(QString &error)
{
    return initTable( &m_archers, &ModelsFacade::archersTable, error );
}

QSqlTableModel *ModelsFacadePrivate::initTable(QSqlTableModel **tableModel, SqlTable (*getTable)(void), QString &error)
{
    if( *tableModel != nullptr )
    {
        return *tableModel;
    }
    SqlTable table = getTable();
    if ( table.init(m_db, error) )
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
