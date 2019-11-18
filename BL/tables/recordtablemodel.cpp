#include "precomp.h"
#include "recordtablemodel.h"
#include "trainingtablemodel.h"
#include "dbtables.h"


RecordTableModel::RecordTableModel(QSqlDatabase& db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingID( core::db::FAKE_ID )
{
    setTable("Record");
}

const core::db::SqlColumnList& RecordTableModel::getColumns() const noexcept
{
    constexpr auto init_cols = +[]{
        using SC = core::db::SqlColumn;
        return std::array{
            SC::createPrimaryKey(FieldType::ftINTEGER),
            SC::createForeign(bl::db::DbTables::Instance().getTable<TrainingTableModel>()),
            SC(u"Record", FieldType::ftTEXT)
        };
    };

    // TODO: constexpr
    static auto cols = init_cols();
    static core::utils::ContainterViewImpl res(cols);
    return res;
}

void RecordTableModel::setTrainingID(core::db::ID trainingID )
{
    if( trainingID != m_trainingID )
    {
        m_trainingID = trainingID;
        if(m_trainingID >= 0)
            setFilter(QString("Training=%0").arg(m_trainingID));
        else
            resetFilter();
        emit trainingIDChanged( m_trainingID );
    }
}

bool RecordTableModel::addRecord(const QString& record)
{
    if(m_trainingID >= 0)
        return insertValues({ m_trainingID, record });
    qDebug() << "Invalid archer core::db::ID";
    return false;
}
