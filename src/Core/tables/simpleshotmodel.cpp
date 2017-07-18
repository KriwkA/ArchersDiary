#include "precomp.h"
#include "simpleshotmodel.h"
#include "diarytables.h"

SimpleShotModel::SimpleShotModel(QSqlDatabase *db, QObject *parent)
    : BaseShotModel( db, parent )
{
    setTable( "SimpleShotModel" );
}


SqlTableModel::SqlColumns SimpleShotModel::getColumns() const
{
    auto trainingStandardModel = DiaryTables::getTableModel( TableType::TrainingStandards );
    if( trainingStandardModel != nullptr )
    {
        SqlTableModel::SqlColumn id = SqlColumn::createPrimaryKey();

        SqlColumn trainingStandard = SqlColumn::createForeign( trainingStandardModel );
        SqlColumn number( "Number", ftINTEGER );
        SqlColumn round( "Round", ftINTEGER );
        SqlColumn score( "Score", ftINTEGER );

        return { id, trainingStandard, number, round, score };
    }
    return SqlColumns();
}

bool SimpleShotModel::addShot(int number, int score)
{
    if( trainingStandardID() != FAKE_ID )
        return insertValues( { number, round(), score } );
    return false;
}
