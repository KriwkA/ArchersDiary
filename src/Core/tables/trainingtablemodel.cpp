#include <precomp.h>
#include "trainingtablemodel.h"
#include "diarytables.h"
#include <QDateTime>

TrainingTableModel::TrainingTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerID( FAKE_ID )
{
    setTable("Training");
}

SqlTableModel::SqlColumns TrainingTableModel::getColumns() const
{    
    auto archerModel = DiaryTables::getTableModel( TableType::Archrers );
    if( archerModel != nullptr )
    {
        SqlTableModel::SqlColumn id = SqlColumn::createPrimaryKey();
        SqlTableModel::SqlColumn archer = SqlColumn::createForeign( archerModel );

        SqlTableModel::SqlColumn date;
        date.name = "Date";
        date.dataType = ftINTEGER;
        return { id, archer, date };
    }    
    return SqlColumns();
}

void TrainingTableModel::setArcherID(ID archerID)
{
    if( m_archerID != archerID )
    {
        m_archerID = archerID;
        if(m_archerID >= 0)
            setFilter(QString("Archer=%0").arg(m_archerID));
        else
            resetFilter();
        emit archerIDChanged( m_archerID );
    }
}

bool TrainingTableModel::addTraining()
{
    if(m_archerID >= 0)
        return insertValues({ m_archerID, QDateTime::currentDateTime().toSecsSinceEpoch() });
    qWarning() << "Invalid archer Id";
    return false;
}
