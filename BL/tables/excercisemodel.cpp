#include "precomp.h"
#include "excercisemodel.h"
#include "diarytables.h"
#include "targetmodel.h"

ExcerciseModel::ExcerciseModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_targetID( FAKE_ID )
{
    setTable( "Excersice" );
}

SqlTableModel::SqlColumns ExcerciseModel::getColumns() const
{
    auto targetsModel = targetModel();
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
        return addExcercise( m_targetID, name, distance, shotsPerSerie, seriesCount );
    return false;
}

int ExcerciseModel::excerciseID(const QString& name) const
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

QString ExcerciseModel::excerciseName(ID excersiceID) const
{
    QSqlRecord rec = recordById( excersiceID );
    if( rec.contains( "Name"))
        return rec.field("Name").value().toString();
    return "Unknown excercise";
}

int ExcerciseModel::shotPerSerie(ID excersiceID) const
{
    QSqlRecord rec = recordById( excersiceID );
    if( rec.contains( "ShotsPerSerie") ) {
        return rec.field("ShotsPerSerie").value().toInt();
    }
    return 0;
}

int ExcerciseModel::seriesCount(ID excersiceID) const
{
    QSqlRecord rec = recordById( excersiceID );
    if( rec.contains( "SeriesCount") ) {
        return rec.field("SeriesCount").value().toInt();
    }
    return 0;
}

bool ExcerciseModel::createTable(QString &error)
{
    if( SqlTableModel::createTable( error ) ) {
        return  addExcercise( Target::getFitaTargetName( 4, 10 ), "12m (30 shots)", 12, 3, 10 ) &&
                addExcercise( Target::getFitaTargetName( 4, 5 ), "18m (30 shots)", 18, 3, 10 ) &&
                addExcercise( Target::getFitaTargetName( 8, 6 ), "30m (36 shots)", 30, 6, 6 )  &&
                addExcercise( Target::getFitaTargetName( 8, 6 ), "40m (36 shots)", 40, 6, 6 )  &&
                addExcercise( Target::getFitaTargetName( 8, 6 ), "50m (36 shots)", 50, 6, 6 )  &&
                addExcercise( Target::getFitaTargetName( 12.2, 10 ), "60m (36 shots)", 60, 6, 6 ) &&
                addExcercise( Target::getFitaTargetName( 12.2, 10 ), "70m (36 shots)", 70, 6, 6 ) &&
                addExcercise( Target::getFitaTargetName( 12.2, 10 ), "90m (36 shots)", 90, 6, 6 );
    }
    return false;
}

bool ExcerciseModel::addExcercise(const QString &targetName, const QString &excersiceName, int distance, int shotsPerSerie, int seriesCount)
{
    auto pTargets = targetModel();
    if( pTargets != nullptr ) {
        ID targetID = pTargets->fitaTargetId( targetName );
        if( targetID != FAKE_ID )
            return addExcercise( targetID, excersiceName, distance, shotsPerSerie, seriesCount );
    }
    return false;
}

bool ExcerciseModel::addExcercise(ID targetID, const QString &excersiceName, int distance, int shotsPerSerie, int seriesCount)
{
    return insertValues( { targetID, excersiceName, distance, shotsPerSerie, seriesCount } );
}

TargetModel *ExcerciseModel::targetModel() const
{
    return static_cast< TargetModel* >( DiaryTables::getTableModel( TableType::Targets ) );
}
