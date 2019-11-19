#include <precomp.h>
#include "trainingtablemodel.h"
#include "archerstablemodel.h"
#include "standardmodel.h"
#include "dbtables.h"


TrainingTableModel::TrainingTableModel(QSqlDatabase& db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerID( core::db::FAKE_ID )    
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
                SC::createForeign(bl::db::DbTables::Instance().getTable<StandardModel>()),
                SC(u"Date", FieldType::ftDATE), // TODO: make as key
        };
    };

    // TODO: constexpr
    static auto cols = init_cols();
    static core::utils::ContainterViewImpl res(cols);
    return res;
}

void TrainingTableModel::setArcherID(core::db::ID archerID)
{
    if( m_archerID != archerID )
    {
        m_archerID = archerID;
        updateFilter();
        select();
        emit archerIDChanged( m_archerID );
    }
}

void TrainingTableModel::setDate(const QDate &date) {
    if(date != m_date) {
        m_date = date;
        updateFilter();
        select();
        emit dateChanged(m_date);
    }
}

void TrainingTableModel::updateFilter()
{
    if(m_archerID != core::db::FAKE_ID ) {
        if(m_date.isNull()) {
            setFilter(QString("[Archer]=%0").arg(m_archerID));
        } else {
            setFilter(QString("[Archer]=%0 AND [Date] BETWEEN %1 AND %2")
                             .arg(m_archerID)
                             .arg(QDateTime(m_date).toMSecsSinceEpoch())
                             .arg(QDateTime(m_date.addDays(1)).toMSecsSinceEpoch()));
        }
    } else {
        resetFilter();
    }
}

bool TrainingTableModel::addTraining(core::db::ID standardID)
{
    if(m_archerID >= 0)
        return insertValues({ m_archerID, standardID, QDateTime::currentDateTime().toMSecsSinceEpoch() });
    qWarning() << "Invalid archer ID";
    return false;
}

