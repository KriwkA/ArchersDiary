#include "precomp.h"
#include "bowstablemodel.h"
#include "archerstablemodel.h"

BowsTableModel::BowsTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerId(-1)
{
    setTable( "Bow" );
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

bool BowsTableModel::addBow(const QString &name, const QString &handle, const QString &limbs, int length, double weight, double base)
{
    if(m_archerId >= 0)
        return insertValues( { m_archerId, name, handle, limbs, length, weight, base } );

    qDebug() << "Invalid archer Id";
    return false;
}


SqlTableModel::SqlColumns BowsTableModel::getColumns() const
{
    ArchersTableModel archers( getDataBase() );
    QString error;
    if( archers.init(error) )
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
        length.name = "Length";
        length.dataType = "INTEGER";

        SqlTableModel::SqlColumn weight;
        weight.name = "Weight";
        weight.dataType = "REAL";

        SqlTableModel::SqlColumn base;
        base.name = "Base";
        base.dataType = "REAL";
        return { id, archer, name, handle, limbs, length, weight, base };
    }
    qCritical() << error;
    return SqlColumns();
}
