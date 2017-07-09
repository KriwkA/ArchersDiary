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

    SqlColumn name;
    name.name = "Name";
    name.dataType = "TEXT";

    SqlColumn circleCount;
    circleCount.name = "CircleCount";
    circleCount.dataType = "INTEGER";

    SqlColumn scores;
    scores.name = "Scores";
    scores.dataType = "BLOB";

    SqlColumn radiuses;
    radiuses.name = "Radiuses";
    radiuses.dataType = "BLOB";

    SqlColumn colors;
    colors.name = "Colors";
    colors.dataType = "BLOB";

    return { id, name, circleCount, scores, radiuses, colors };
}

bool TargetModel::init( QString &error )
{
    if( SqlTableModel::init( error ) )
    {
        if( rowCount() != 0 )
            return true;

        return addTarget( Target::getFitaTarget( 4.0, 10 ) ) &&
               addTarget( Target::getFitaTarget( 4.0, 5 ) ) &&
               addTarget( Target::getFitaTarget( 8.0, 10 ) ) &&
               addTarget( Target::getFitaTarget( 8.0, 6 ) ) &&
               addTarget( Target::getFitaTarget( 12.2, 10 ) );
    }
    return false;
}

bool TargetModel::addTarget(const Target &target)
{
    int count = target.circleCount;


    if( count == target.scores.size() && count == target.radiuses.size() && count == target.colors.size() )
    {
        auto s = Serilization::serialize( target.scores );
        auto r = Serilization::serialize( target.radiuses );
        auto c = Serilization::serialize( target.colors );
        return insertValues( { target.name, count, r, c, s } );
    }

    return false;
}


Target Target::getFitaTarget(double tenSize, int circleCount)
{
    Target target;
    target.name = QString( "FITA %0cm, %1 circles" ).arg( tenSize * 10.0 ).arg( circleCount );
    target.circleCount = circleCount;
    double radius = tenSize;
    for(int i = 0, score = 10;
        i < circleCount;
        ++i, radius += tenSize, --score)
    {
        target.colors.append( getFitaColor( score ));
        target.radiuses.append( radius );
        target.scores.append( score );
    }
    return target;
}

int Target::getFitaColor(int score)
{
    switch( score )
    {
    case 1: return 0xFFFFFF;
    case 2: return 0xFFFFFF;
    case 3: return 0x000000;
    case 4: return 0x000000;
    case 5: return 0x0000FF;
    case 6: return 0x0000FF;
    case 7: return 0xFF0000;
    case 8: return 0xFF0000;
    case 9: return 0xFFFF00;
    case 10: return 0xFFFF00;
    }
    return 0;
}
