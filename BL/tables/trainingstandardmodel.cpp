#include "precomp.h"
#include "trainingstandardmodel.h"
#include "shotmodel.h"
#include "diarytables.h"

TrainingStandardModel::TrainingStandardModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingID( FAKE_ID )
{
    setTable( "TrainingStandard" );
}

SqlTableModel::SqlColumns TrainingStandardModel::getColumns() const
{
    auto trainingModel = DiaryTables::getTableModel( TableType::Trainings );
    auto standardModel = DiaryTables::getTableModel( TableType::Standards );
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
    auto shots = DiaryTables::getTableModel( TableType::Shots );
    if( !( shots == nullptr || m_trainingID == FAKE_ID ) ) {
        return insertValues( { m_trainingID, standardID } );
    }
    return false;
}