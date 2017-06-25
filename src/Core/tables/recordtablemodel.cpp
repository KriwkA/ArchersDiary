#include "precomp.h"
#include "recordtablemodel.h"
#include "diarytables.h"

RecordTableModel::RecordTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingId( FAKE_ID )
{
    setTable("Record");
}

SqlTableModel::SqlColumns RecordTableModel::getColumns() const
{
    auto trainingModel = reinterpret_cast<SqlTableModel*>(DiaryTables::getObject()->trainingModel());
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

void RecordTableModel::setTrainingID(ID trainingId)
{
    m_trainingId = trainingId;
    if(m_trainingId >= 0)
        setFilter(QString("Training=%0").arg(m_trainingId));
    else
        resetFilter();
}

bool RecordTableModel::addRecord(const QString& record)
{
    if(m_trainingId >= 0)
        return insertValues({ m_trainingId, record });
    qDebug() << "Invalid archer Id";
    return false;
}
