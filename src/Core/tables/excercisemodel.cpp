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
    auto targetsModel = DiaryTables::getTableModel( TableType::Targets );
    if( targetsModel != nullptr )
    {
        SqlColumn id = SqlColumn::createPrimaryKey();

        SqlColumn target = SqlColumn::createForeign( targetsModel );

        SqlColumn name;
        name.name = "Name";
        name.dataType = ftTEXT;

        SqlColumn distance;
        distance.name = "Distance";
        distance.dataType = ftINTEGER;

        SqlColumn shotsPerSerie;
        shotsPerSerie.name = "ShotsPerSerie";
        shotsPerSerie.dataType = ftINTEGER;

        SqlColumn seriesCount;
        seriesCount.name = "SeriesCount";
        seriesCount.dataType = ftINTEGER;

        return { id, target, name, distance, shotsPerSerie, seriesCount };
    }
    return SqlColumns();
}

void ExcerciseModel::setTargetID(ID targetID)
{
    if( m_targetID != targetID )
    {
        m_targetID = targetID;
        if( m_targetID != FAKE_ID )
            setFilter( QString("Target=%0").arg(m_targetID) );
        else
            resetFilter();
        emit targetIDChanged( m_targetID );
    }
}

bool ExcerciseModel::addExcercise(const QString &name, int distance, int shotsPerSerie, int seriesCount)
{
    if( m_targetID != FAKE_ID )
        return insertValues( { name, distance, shotsPerSerie, seriesCount } );
    return false;
}

