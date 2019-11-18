#include <precomp.h>
#include "trainingtablemodel.h"
#include "archerstablemodel.h"
#include "dbtables.h"
#include <array>

#include <QDateTime>

TrainingTableModel::TrainingTableModel(QSqlDatabase& db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerID( core::db::FAKE_ID )
    , m_currentTrainingID( core::db::FAKE_ID )
{
    setTable("Training");
}

const core::db::SqlColumnList& TrainingTableModel::getColumns() const noexcept
{
    constexpr auto init_cols = +[]{
        using SC = core::db::SqlColumn;
        return std::array{
                SC::createPrimaryKey(FieldType::ftINTEGER),
                SC::createForeign(bl::db::DbTables::Instance().getTable<ArchersTableModel>()),
                SC(u"Date", FieldType::ftDATE),
                SC(u"SimpleShots", FieldType::ftINTEGER)
        };
    };

    // TODO: constexpr
    static auto cols = init_cols();
    static core::utils::ContainterViewImpl res(cols);
    return res;
}

bool TrainingTableModel::select()
{
    if( SqlTableModel::select() ) {
        if( m_archerID != core::db::FAKE_ID ) {
            emit shotCountChanged( shotCount() );
        }
        return true;
    }
    return false;
}

void TrainingTableModel::setArcherID(core::db::ID archerID)
{
    if( m_archerID != archerID )
    {
        m_archerID = archerID;
        if(m_archerID != core::db::FAKE_ID )
            setFilter(QString("Archer=%0").arg(m_archerID));
        else
            resetFilter();
        emit archerIDChanged( m_archerID );
    }
}

int TrainingTableModel::shotCount() const
{
    auto modelIndex = currentTrainingModelIndex();
    if( modelIndex.isValid() ) {
        return data( modelIndex, roleFromRoleName( "SimpleShots" ) ).toInt();
    }
    return 0;
}

void TrainingTableModel::setShotCount(int shotCount)
{
    if( shotCount != this->shotCount() ) {
        auto modelIndex = currentTrainingModelIndex();
        if( modelIndex.isValid() && setData( modelIndex.row(), shotCount, roleFromRoleName( "SimpleShots" ) ) )
            emit shotCountChanged( shotCount );        
    }
}

QModelIndex TrainingTableModel::currentTrainingModelIndex() const
{
    if( m_currentTrainingID != core::db::FAKE_ID )
    {
        int rows = rowCount();
        QModelIndex modelIndex;
        bool ok = false;
        for( int i = 0; i < rows; ++i ) {
            modelIndex = index(i, 0);
            if( data( modelIndex, roleFromRoleName( "Id" ) ).toInt( &ok ) == m_currentTrainingID && ok )
                return modelIndex;
        }
    }

    return QModelIndex();
}

bool TrainingTableModel::addTraining()
{
    if(m_archerID >= 0)
        return insertValues({ m_archerID, QDateTime::currentDateTime().toSecsSinceEpoch(), 0 });
    qWarning() << "Invalid archer core::db::ID";
    return false;
}

