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
        SqlColumn trainingStandard = SqlColumn::createForeign( trainingStandardModel );

        SqlColumn number;
        number.name = "Number";
        number.dataType = ftINTEGER;

        SqlColumn score;
        number.name = "SCORE";
        number.dataType = ftINTEGER;

        return { trainingStandard, number, score };
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
