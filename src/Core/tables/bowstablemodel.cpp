#include "precomp.h"
#include "bowstablemodel.h"

BowsTableModel::BowsTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, "Bow", getColumns(), parent)
    , m_archerId(-1)
{
}

ID BowsTableModel::getArcherId() const
{
    return m_archerId;
}

void BowsTableModel::setArcherId(ID archerId)
{
    m_archerId = archerId;
    if(m_archerId >= 0)
        setFilter(QString("Archer=%0").arg(m_archerId));
    else
        setFilter(QString(""));
}

void BowsTableModel::addBow(const QString &name, const QString &handle, const QString &limbs, int length, double weight, double base)
{
    if(m_archerId >= 0)
    {
        QStringList names = {"Archer", "Name", "Handle", "Limbs", "Length", "Weight", "Base"};

        QStringList values = {
            QString::number(m_archerId),
            '"' + name + '"',
            '"' + handle + '"',
            '"' + limbs + '"',
            QString::number(length),
            QString::number(weight),
            QString::number(base)
        };
        insertAllValues(names, values);
    }
    else
        qDebug() << "Invalid archer Id";
}


SqlTableModel::SqlColumns BowsTableModel::getColumns() const
{
    SqlTableModel::SqlColumn id;
    id.name = "Id";
    id.dataType = "INTEGER";
    id.type = SqlTableModel::PRIMARY_KEY;

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

    SqlTableModel::SqlColumn handle;
    handle.name = "Handle";
    handle.dataType = "TEXT";

    SqlTableModel::SqlColumn limbs;
    limbs.name = "Limbs";
    limbs.dataType = "TEXT";

    SqlTableModel::SqlColumn length;
    limbs.name = "Length";
    limbs.dataType = "INTEGER";

    SqlTableModel::SqlColumn weight;
    weight.name = "Weight";
    weight.dataType = "REAL";

    SqlTableModel::SqlColumn base;
    base.name = "Base";
    base.dataType = "REAL";


    return { id, archer, name, handle, limbs, length, weight, base };
}
