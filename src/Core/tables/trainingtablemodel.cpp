#include <precomp.h>
#include "trainingtablemodel.h"
#include "diarytables.h"
#include <QDateTime>

TrainingTableModel::TrainingTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerId( FAKE_ID )
{
    setTable("Training");
}

SqlTableModel::SqlColumns TrainingTableModel::getColumns() const
{    
    auto archerModel = reinterpret_cast<SqlTableModel*>(DiaryTables::getObject()->archersModel());
    if( archerModel != nullptr )
    {

        SqlTableModel::SqlColumn archer = SqlColumn::createForeign( archerModel );

        SqlTableModel::SqlColumn date;
        date.name = "Date";
        date.dataType = "INTEGER";
        return { archer, date };
    }    
    return SqlColumns();
}

void TrainingTableModel::setArcherId(ID archerId)
{
    m_archerId = archerId;
    if(m_archerId >= 0)
        setFilter(QString("Archer=%0").arg(m_archerId));
    else
        resetFilter();
}

bool TrainingTableModel::addTraining()
{
    if(m_archerId >= 0)
        return insertValues({ m_archerId, QDateTime::currentDateTime().toSecsSinceEpoch() });
    qWarning() << "Invalid archer Id";
    return false;
}
