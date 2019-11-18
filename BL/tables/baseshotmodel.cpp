#include <precomp.h>
#include "baseshotmodel.h"

BaseShotModel::BaseShotModel( QSqlDatabase& db, QObject* parent )
    : SqlTableModel( db, parent )
    , m_trainingStandardID( core::db::FAKE_ID )
    , m_round( 0 )
{
}

void BaseShotModel::setTrainingStandardID(const core::db::ID &trainingStandardID)
{
    if( m_trainingStandardID != trainingStandardID )
    {
        m_trainingStandardID = trainingStandardID;
        updateFilter();
        emit trainingStandardIDChanged( m_trainingStandardID );
        select();
    }
}

void BaseShotModel::setRound(int round)
{
    if (m_round == round)
        return;

    m_round = round;
    updateFilter();
    select();
    emit roundChanged(m_round);
}

void BaseShotModel::resetFilter()
{
    setFilter( QString("Round=%0").arg(m_round) );
}

void BaseShotModel::updateFilter()
{
    if( m_trainingStandardID != core::db::FAKE_ID ) {
        setFilter( QString("TrainingStandard=%0 AND Round=%1").arg( m_trainingStandardID ).arg(m_round) );
    }
    else
        resetFilter();
}
