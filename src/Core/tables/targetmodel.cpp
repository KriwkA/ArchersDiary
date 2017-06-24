#include "precomp.h"
#include "targetmodel.h"

TargetModel::TargetModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
{
    setTable( "Target" );
}

SqlTableModel::SqlColumns TargetModel::getColumns() const
{    
    SqlColumn id = SqlColumn::createPrimaryKey();

    SqlColumn circleCount;
    circleCount.name = "CircleCount";
    circleCount.dataType = "INTEGER";

    SqlColumn growingRadius;
    growingRadius.name = "GrowingRadius";
    growingRadius.dataType = "INTEGER";

    SqlColumn circleColors;
    circleColors.name = "CircleColors";
    circleColors.dataType = "BLOB";

    return { id, circleCount, growingRadius, circleColors };
}

bool TargetModel::addTarget(int circleCount, int growingRadius, const QList<int> &circleColors)
{       
    QVariantList colors;
    for( int color : circleColors )
        colors.append( color );
    if( circleCount == circleColors.size() )
        return insertValues( { circleCount, growingRadius, colors } );
    return false;
}
