#include <precomp.h>
#include "trainingstandardmodel.h"
#include "shotmodel.h"
#include "standardmodel.h"
#include "trainingtablemodel.h"
#include "dbtables.h"

TrainingStandardModel::TrainingStandardModel(QSqlDatabase& db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingID( core::db::FAKE_ID )
{
    setTable( "TrainingStandard" );
}

const core::db::SqlColumnList& TrainingStandardModel::getColumns() const noexcept
{
    constexpr auto InitCols = +[]{
        using SC = core::db::SqlColumn;
        return std::array{
                SC::createPrimaryKey(FieldType::ftINTEGER),
                SC::createForeign(bl::db::DbTables::Instance().getTable<TrainingTableModel>()),
                SC::createForeign(bl::db::DbTables::Instance().getTable<StandardModel>())
        };
    };

    // TODO: constexpr
    static auto cols = InitCols();
    static core::utils::ContainterViewImpl res(cols);
    return res;
}

void TrainingStandardModel::setTrainingID(core::db::ID trainingID)
{
    if( m_trainingID != trainingID )
    {
        m_trainingID = trainingID;
        if( m_trainingID != core::db::FAKE_ID )
            setFilter( QString("Training=%0").arg( m_trainingID ) );
        else
            resetFilter();
        emit trainingIDChanged( m_trainingID );
    }
}

bool TrainingStandardModel::addStandard(core::db::ID standardID)
{
    if(m_trainingID != core::db::FAKE_ID) {

        // TODO: раньше для чего-то создавалось, нужно проверить нужно ли это вообще
        bl::db::DbTables::Instance().getTable<ShotModel>();

        return insertValues( { m_trainingID, standardID } );
    }
    return false;
}
