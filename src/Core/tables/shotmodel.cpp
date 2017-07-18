#include "precomp.h"
#include "shotmodel.h"
#include "diarytables.h"

ShotModel::ShotModel(QSqlDatabase *db, QObject *parent)
    : BaseShotModel( db, parent )
{
    setTable( "ShotModel" );
}

SqlTableModel::SqlColumns ShotModel::getColumns() const
{
    auto trainingStandardModel = DiaryTables::getTableModel( TableType::TrainingStandards );
    if( trainingStandardModel != nullptr )
    {
        SqlTableModel::SqlColumn id = SqlColumn::createPrimaryKey();
        SqlColumn trainingStandard = SqlColumn::createForeign( trainingStandardModel );
        SqlColumn number( "Number", ftINTEGER );
        SqlColumn round( "Round", ftINTEGER );
        SqlColumn radius( "Radius", ftREAL );
        SqlColumn alpha( "Alpha", ftREAL );
        SqlColumn arrowDiameter( "ArrowDiameter", ftREAL );

        return { id, trainingStandard, number, round,  radius, alpha, arrowDiameter };
    }
    return SqlColumns();
}

bool ShotModel::addShot(int number, double radius, double alpha, double arrowDiameter)
{
    if( trainingStandardID() != FAKE_ID )
        return insertValues( { number, round(), radius, alpha, arrowDiameter } );
    return false;
}


