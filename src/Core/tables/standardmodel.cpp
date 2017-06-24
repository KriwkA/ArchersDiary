#include "precomp.h"
#include "standardmodel.h"

StandardModel::StandardModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
{
    setTable( "Standard" );
}

SqlTableModel::SqlColumns StandardModel::getColumns() const
{
    SqlColumn id = SqlColumn::createPrimaryKey();

    SqlColumn name;
    name.name = "Name";
    name.dataType = "TEXT";

    return { id, name };
}

bool StandardModel::addStandard(const QString &name)
{
    return insertValues( { name } );
}
