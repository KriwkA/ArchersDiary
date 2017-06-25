#include "precomp.h"
#include "excercisemodel.h"
#include "diarytables.h"

ExcerciseModel::ExcerciseModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_targetID( FAKE_ID )
{
    setTable( "Excersice" );
}

SqlTableModel::SqlColumns ExcerciseModel::getColumns() const
{
    auto targetsModel = reinterpret_cast<SqlTableModel*>( DiaryTables::getObject()->targetModel() );
    if( targetsModel != nullptr )
    {
        SqlColumn id = SqlColumn::createPrimaryKey();

        SqlColumn target = SqlColumn::createForeign( targetsModel );

        SqlColumn name;
        name.name = "Name";
        name.dataType = "TEXT";

        SqlColumn distance;
        distance.name = "Distance";
        distance.dataType = "INTEGER";

        SqlColumn shotsPerSerie;
        shotsPerSerie.name = "ShotsPerSerie";
        shotsPerSerie.dataType = "INTEGER";

        SqlColumn seriesCount;
        seriesCount.name = "SeriesCount";
        seriesCount.dataType = "INTEGER";

        return { id, target, name, distance, shotsPerSerie, seriesCount };
    }
    return SqlColumns();
}

void ExcerciseModel::setTargetID(ID targetID)
{
    m_targetID = targetID;
    if( m_targetID != FAKE_ID )
        setFilter( QString("Target=%0").arg(m_targetID) );
    else
        resetFilter();
}

bool ExcerciseModel::addExcercise(const QString &name, int distance, int shotsPerSerie, int seriesCount)
{
    if( m_targetID != FAKE_ID )
        return insertValues( { name, distance, shotsPerSerie, seriesCount } );
    return false;
}

