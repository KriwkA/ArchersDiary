#include "precomp.h"
#include "recordtablemodel.h"
#include "diarytables.h"

RecordTableModel::RecordTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingId( -1 )
{
    setTable("Record");
}

SqlTableModel::SqlColumns RecordTableModel::getColumns() const
{
    auto trainingModel = reinterpret_cast<SqlTableModel*>(DiaryTables::getObject()->trainingModel());
    if( trainingModel != nullptr )
    {
        SqlTableModel::SqlColumn training;
        training.name = trainingModel->tableName();
        training.dataType = "INTEGER";
        training.type = SqlTableModel::FOREIGN_KEY;
        training.foreignFlags = ForeignFlags(OnDeleteCascade | OnUpdateCascade);
        training.foreignTable = trainingModel->tableName();
        training.foreingField = "Id";

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
        setFilter(QString(""));
}

bool RecordTableModel::addRecord(const QString& record)
{
    if(m_trainingId >= 0)
        return insertValues({ m_trainingId, record });
    qDebug() << "Invalid archer Id";
    return false;
}
