#include "archerstablemodel.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QDebug>

ArchersTableModel::ArchersTableModel(QSqlDatabase* db, QObject *parent)
    : SqlTableModel(db, "Archer", getColumns(), parent)
{

}

void ArchersTableModel::addArcher(const QString &archerName)
{
    QSqlField id("Id", QVariant::Int);

    QSqlField name("Name", QVariant::String);
    name.setValue( archerName );

    QSqlRecord rec;
    rec.append(id);
    rec.append(name);    

    if( !insertRecord(rowCount(), rec) )
    {
       qDebug() << "Insert record error: " << this->lastError().text();
    }
}

SqlTableModel::SqlColumns ArchersTableModel::getColumns()
{
    SqlTableModel::SqlColumn id;
    id.name = "Id";
    id.dataType = "INTEGER";
    id.type = SqlTableModel::PRIMARY_KEY;

    SqlTableModel::SqlColumn name;
    name.name = "Name";
    name.dataType = "TEXT";

    return { id, name };
}
