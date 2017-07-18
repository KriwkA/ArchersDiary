#include "precomp.h"
#include "simpleshotmodel.h"
#include "diarytables.h"

SimpleShotModel::SimpleShotModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingStandardID( FAKE_ID )
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

void SimpleShotModel::setTrainingStandardID(const ID &trainingStandardID)
{
    if( m_trainingStandardID != trainingStandardID )
    {
        m_trainingStandardID = trainingStandardID;
        if( m_trainingStandardID != FAKE_ID )
            setFilter( QString("TrainingStandard=%0").arg( m_trainingStandardID ));
        else
            resetFilter();
        emit trainingStandardIDChanged( m_trainingStandardID );
    }
}

bool SimpleShotModel::addShot(int number, int score)
{
    if( m_trainingStandardID != FAKE_ID )
        return insertValues( { number, score } );
    return false;
}
