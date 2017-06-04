#include "sqltable.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

SqlTable::SqlTable(){}

SqlTable::SqlTable(const QString &name)
    : m_name(name)
{
}

SqlTable::SqlTable(const QString &name, const SqlTable::SqlColumns &columns)
    : m_name(name)
    , m_columns(columns)
{
}

SqlTable::~SqlTable(){}

bool SqlTable::init(QSqlDatabase *db, QString &error)
{
    if( db != nullptr )
    {
        if( openDatabase(db, error) && createTable(db, error) )
        {
            return true;
        }
    }
    else
    {
        error = "db is nullptr";
    }

    return false;
}

bool SqlTable::insertValues(QSqlDatabase *db, const QVariantList &values, QString &error)
{
    return insertValues(db, QStringList(), values, error);
}

bool SqlTable::insertValues(QSqlDatabase *db, const QStringList &colNames, const QVariantList &values, QString &error)
{
    if(openDatabase( db, error ) && values.size())
    {
        if(colNames.size() == 0 || colNames.size() == values.size())
        {
            QString queryString;
            if(colNames.size() == 0)
                queryString = QString("INSERT INTO %0 values ").arg( m_name );
            else
                queryString = QString("INSERT INTO %0 (%1) values ").arg( m_name ).arg(colNames.join(", "));

            queryString.reserve( queryString.length() * (values.count() + 1) );

            QStringList valuesStrs;
            valuesStrs.reserve(values.size());
            for(const auto& val : values)
                valuesStrs.append(val.toString());

            queryString.append(QString("(%0)").arg(valuesStrs.join(", ")));

            queryString.append(';');
            return execQuery(db, queryString, error);
        }
        else
            error = "Names count not equal values count";
    }
    else
        error = "Values list is empty";

    return false;
}

bool SqlTable::createTable(QSqlDatabase *db, QString &error)
{
    QString queryString = QString("CREATE TABLE IF NOT EXISTS %0").arg( m_name );
    queryString.reserve( queryString.length() * (m_columns.count() + 1) * 2 );


    QStringList fields;
    for(const auto& col : m_columns)
    {
        QString fieldStr = QString("%0 %1").arg( col.name ).arg( col.dataType );
        switch (col.type) {
        case PRIMARY_KEY:
                fieldStr.append(" PRIMARY_KEY");
            break;
        case FOREIGN_KEY:
            fieldStr.append(QString(" REFERENCES %0(%1)").arg(col.foreignTable).arg(col.foreingField));
            if(col.foreignFlags & OnDeleteCascade)
                fieldStr.append(" ON DELETE CASCADE");
            if(col.foreignFlags & OnUpdateCascade)
                fieldStr.append(" ON UPDATE CASCADE");
            break;
        }
        fields.append(fieldStr);
    }
    if(fields.size())
        queryString.append(QString("(%0)").arg(fields.join(", ")));

    queryString.append(';');

    return execQuery(db, queryString, error);
}

bool SqlTable::openDatabase(QSqlDatabase *db, QString &error)
{
    if( db->isOpen() || db->open() )
        return true;
    error = "Database not opened: " + db->lastError().text();
    return false;
}

bool SqlTable::execQuery(QSqlDatabase *db, const QString &queryString, QString& error)
{
    QSqlQuery query(*db);
    if(query.exec(queryString))
        return true;
    error = query.lastError().text();
    return false;
}
