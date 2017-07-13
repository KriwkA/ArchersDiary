#include "precomp.h"
#include "shotmodel.h"
#include "diarytables.h"

ShotModel::ShotModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingStandardID( FAKE_ID )
{
    setTable( "ShotModel" );
}

SqlTableModel::SqlColumns ShotModel::getColumns() const
{
    auto trainingStandardModel = DiaryTables::getTableModel( TableType::TrainingStandards );
    if( trainingStandardModel != nullptr )
    {
        SqlColumn trainingStandard = SqlColumn::createForeign( trainingStandardModel );

        SqlColumn number;
        number.name = "Number";
        number.dataType = ftINTEGER;

        SqlColumn radius;
        radius.name = "Radius";
        radius.dataType = ftREAL;

        SqlColumn alpha;
        alpha.name = "Alpha";
        alpha.dataType = ftREAL;

        SqlColumn arrowDiameter;
        arrowDiameter.name = "ArrowDiameter";
        arrowDiameter.dataType = ftREAL;

        return { trainingStandard, number, radius, alpha, arrowDiameter };
    }
    return SqlColumns();
}

void ShotModel::setTrainingStandardID(const ID &trainingStandardID)
{
    if( m_trainingStandardID != trainingStandardID )
    {
        m_trainingStandardID = trainingStandardID;
        if( m_trainingStandardID != FAKE_ID )
            setFilter( "TrainingStandard=%0" );
        else
            resetFilter();
        emit trainingStandardIDChanged( m_trainingStandardID );
    }
}

bool ShotModel::addShot(int number, double radius, double alpha, double arrowDiameter)
{
    if( m_trainingStandardID != FAKE_ID )
        return insertValues( { number, radius, alpha, arrowDiameter } );
    return false;
}


