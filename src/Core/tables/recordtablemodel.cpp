#include "precomp.h"
#include "recordtablemodel.h"
#include "diarytables.h"

RecordTableModel::RecordTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingID( FAKE_ID )
{
    setTable("Record");
}

SqlTableModel::SqlColumns RecordTableModel::getColumns() const
{
    auto trainingModel = DiaryTables::getTableModel( TableType::Trainings );
    if( trainingModel != nullptr )
    {
        SqlTableModel::SqlColumn training = SqlColumn::createForeign( trainingModel );

        SqlColumn record;
        record.name = "Record";
        record.dataType = "TEXT";
        return { training, record };
    }
    return SqlColumns();
}

void RecordTableModel::setTrainingID(ID trainingID )
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
    qDebug() << "Invalid archer Id";
    return false;
}
