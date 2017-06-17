#include "precomp.h"
#include "archerstablemodel.h"

ArchersTableModel::ArchersTableModel(QSqlDatabase* db, QObject *parent)
    : SqlTableModel(db, parent)
{
    setTable( "Archer" );
}

bool ArchersTableModel::addArcher(const QString &archerName)
{    
    return insertValues( { archerName } );
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
