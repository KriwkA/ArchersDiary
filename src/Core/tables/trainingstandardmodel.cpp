#include "precomp.h"
#include "trainingstandardmodel.h"

TrainingStandardModel::TrainingStandardModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingID( FAKE_ID )
{
    setTable( "TrainingStandard" );
}

SqlTableModel::SqlColumns TrainingStandardModel::getColumns() const
{
    auto trainingModel = reinterpret_cast<SqlTableModel*>( DiaryTables::getObject()->trainingModel() );
    auto standardModel = reinterpret_cast<SqlTableModel*>( DiaryTables::getObject()->standardModel() );

    if( trainingModel != nullptr && standardModel != nullptr )
    {
        SqlColumn id = SqlColumn::createPrimaryKey();
        SqlColumn training = SqlColumn::createForeign( trainingModel );
        SqlColumn standard = SqlColumn::createForeign( standardModel );
        return { id, training, standard };
    }
    return SqlColumns();
}

void TrainingStandardModel::setTrainingID(ID trainingID)
{
    if( m_trainingID != trainingID )
    {
        m_trainingID = trainingID;
        if( m_trainingID != FAKE_ID )
            setFilter( QString("Training=%0").arg( m_trainingID ) );
        else
            resetFilter();
        emit trainingIDChanged( m_trainingID );
    }
}

bool TrainingStandardModel::addStandard(ID standardID)
{
    if( m_trainingID != FAKE_ID )
        return insertValues( { m_trainingID, standardID } );
    return false;
}
