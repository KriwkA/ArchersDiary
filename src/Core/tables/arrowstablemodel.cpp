#include "arrowstablemodel.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ArrowsTableModel::ArrowsTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, "Arrow", getColumns(), parent)
    , m_archerId(-1)
{

}

SqlTableModel::SqlColumns ArrowsTableModel::getColumns()
{
    SqlTableModel::SqlColumn archer;
    archer.name = "Archer";
    archer.dataType = "INTEGER";
    archer.type = SqlTableModel::FOREIGN_KEY;
    archer.foreignFlags = ForeignFlags(OnDeleteCascade | OnUpdateCascade);
    archer.foreignTable = "Archer";
    archer.foreingField = "Id";

    SqlTableModel::SqlColumn name;
    name.name = "Name";
    name.dataType = "TEXT";

    SqlTableModel::SqlColumn spine;
    spine.name = "Spine";
    spine.dataType = "REAL";

    SqlTableModel::SqlColumn length;
    length.name = "Length";
    length.dataType = "REAL";

    SqlTableModel::SqlColumn diameter;
    diameter.name = "Diameter";
    diameter.dataType = "REAL";

    return { archer, name, spine, length, diameter };
}

long long ArrowsTableModel::getArcherId() const
{
    return m_archerId;
}

void ArrowsTableModel::setArcherId(long long archerId)
{
    m_archerId = archerId;
    if(m_archerId >= 0)
        setFilter(QString("Archer=%0").arg(m_archerId));
    else
        setFilter(QString(""));
}

void ArrowsTableModel::addArrow(const QString &name, double spine, double length, double diameter)
{
    if(m_archerId >= 0)
    {
        QString queryStr = QString("INSERT INTO Arrow VALUES (%0, %1, %2, %3, %4)")
                              .arg(m_archerId)
                              .arg('"' + name + '"')
                              .arg(spine)
                              .arg(length)
                              .arg(diameter);

        QSqlQuery query;

        if(!query.exec(queryStr))
        {
            qDebug() << query.lastQuery();
            qDebug() << query.lastError().text();
        }

    }
    else
        qDebug() << "Invalid archer Id";
}
