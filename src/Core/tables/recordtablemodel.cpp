#include "precomp.h"
#include "recordtablemodel.h"
#include "trainingtablemodel.h"

RecordTableModel::RecordTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_trainingId( -1 )
{
    setTable("Record");
}

SqlTableModel::SqlColumns RecordTableModel::getColumns() const
{
    TrainingTableModel trainings( getDataBase() );
    QString error;
    if(trainings.init(error))
    {
        SqlTableModel::SqlColumn training;
        training.name = trainings.tableName();
        training.dataType = "INTEGER";
        training.type = SqlTableModel::FOREIGN_KEY;
        training.foreignFlags = ForeignFlags(OnDeleteCascade | OnUpdateCascade);
        training.foreignTable = trainings.tableName();
        training.foreingField = "Id";

        SqlColumn record;
        record.name = "Record";
        record.dataType = "TEXT";
        return { training, record };
    }
    qCritical() << error;
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
