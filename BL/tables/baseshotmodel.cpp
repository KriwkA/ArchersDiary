#include <precomp.h>
#include "baseshotmodel.h"

BaseShotModel::BaseShotModel( QSqlDatabase& db, QObject* parent )
    : SqlTableModel( db, parent )
    , m_trainingID( core::db::FAKE_ID )
    , m_round( 0 )
{
}

void BaseShotModel::setTrainingID(const core::db::ID &trainingID)
{
    if( m_trainingID != trainingID )
    {
        m_trainingID = trainingID;
        updateFilter();
        select();
        emit trainingIDChanged( m_trainingID );
    }
}

void BaseShotModel::setRound(int round)
{
    if (m_round != round) {
        m_round = round;
        updateFilter();
        select();
        emit roundChanged(m_round);
    }
}

void BaseShotModel::resetFilter()
{
    setFilter( QString("[Round]=%0").arg(m_round) );
}

void BaseShotModel::updateFilter()
{
    if( m_trainingID != core::db::FAKE_ID ) {
        setFilter( QString("[Training]=%0 AND [Round]=%1").arg( m_trainingID ).arg(m_round) );
    } else {
        resetFilter();
    }
}
