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
    name.dataType = ftTEXT;

    return { id, name };
}

bool StandardModel::addStandard(const QString &name)
{
    return insertValues( { name } );
}

int StandardModel::standardId( const QString &name )
{
    int rows = rowCount();
    QSqlRecord rec;
    for(int i = 0; i < rows; ++i) {
        rec = record(i);
        if( rec.field("Name").value().toString() == name )
            return rec.field("Id").value().toInt();
    }
    return FAKE_ID;
}

bool StandardModel::createTable(QString &error)
{
    if( SqlTableModel::createTable( error ) )
    {
        return  addStandard( "12m (30 shots)" ) &&
                addStandard( "18m (30 shots)" ) &&
                addStandard( "30m (36 shots)" ) &&
                addStandard( "50m (36 shots)" ) &&
                addStandard( "60m (36 shots)" ) &&
                addStandard( "70m (36 shots)" ) &&
                addStandard( "90m (36 shots)" ) &&

                addStandard( "12m (60 shots)") &&
                addStandard( "18m (60 shots)") &&
                addStandard( "30m (72 shots)") &&
                addStandard( "50m (72 shots)") &&
                addStandard( "60m (72 shots)") &&
                addStandard( "70m (72 shots)") &&
                addStandard( "90m (72 shots)") &&

                addStandard( "60m, 50m, 40m, 30m (144 shots)") &&
                addStandard( "90m, 70m, 50m, 30m (144 shots)") &&
                addStandard( "70m, 60m, 50m, 30m (144 shots)");
    }
    return false;
}
