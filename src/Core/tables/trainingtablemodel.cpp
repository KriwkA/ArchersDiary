#include <precomp.h>
#include "trainingtablemodel.h"
#include <QDateTime>

TrainingTableModel::TrainingTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerId( -1 )
{
    setTable("Training");
}

SqlTableModel::SqlColumns TrainingTableModel::getColumns() const
{
    SqlTableModel::SqlColumn archer;
    archer.name = "Archer";
    archer.dataType = "INTEGER";
    archer.type = SqlTableModel::FOREIGN_KEY;
    archer.foreignFlags = ForeignFlags(OnDeleteCascade | OnUpdateCascade);
    archer.foreignTable = "Archer";
    archer.foreingField = "Id";

    SqlTableModel::SqlColumn date;
    date.name = "Date";
    date.dataType = "INTEGER";

    return { archer, date };
}

void TrainingTableModel::setArcherId(ID archerId)
{
    m_archerId = archerId;
    if(m_archerId >= 0)
        setFilter(QString("Archer=%0").arg(m_archerId));
    else
        setFilter(QString(""));
}

bool TrainingTableModel::addTraining()
{
    if(m_archerId >= 0)
        return insertValues({ m_archerId, QDateTime::currentDateTime().toSecsSinceEpoch() });
    qDebug() << "Invalid archer Id";
    return false;
}
