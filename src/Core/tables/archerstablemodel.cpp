#include "precomp.h"
#include "archerstablemodel.h"

ArchersTableModel::ArchersTableModel(QSqlDatabase* db, QObject *parent)
    : SqlTableModel(db, "Archer", getColumns(), parent)
{

}

void ArchersTableModel::addArcher(const QString &archerName)
{
    QStringList names = { "Name" };
    QStringList values = { '"' + archerName + '"' };
    insertAllValues(names, values);
}

SqlTableModel::SqlColumns ArchersTableModel::getColumns() const
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
