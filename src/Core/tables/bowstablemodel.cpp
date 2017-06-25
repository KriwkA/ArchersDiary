#include "precomp.h"
#include "bowstablemodel.h"
#include "diarytables.h"

BowsTableModel::BowsTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerId( FAKE_ID )
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
    if( m_archerId != FAKE_ID )
        setFilter(QString("Archer=%0").arg(m_archerId));
    else
        resetFilter();
}

bool BowsTableModel::addBow(const QString &name, const QString &handle, const QString &limbs, int length, double weight, double base)
{
    if(m_archerId !=  FAKE_ID )
        return insertValues( { m_archerId, name, handle, limbs, length, weight, base } );

    qDebug() << "Invalid archer Id";
    return false;
}


SqlTableModel::SqlColumns BowsTableModel::getColumns() const
{
    auto archersModel = reinterpret_cast<SqlTableModel*>(DiaryTables::getObject()->archersModel());
    if( archersModel != nullptr )
    {
        SqlColumn id = SqlColumn::createPrimaryKey();

        SqlColumn archer = SqlColumn::createForeign( archersModel );

        SqlColumn name;
        name.name = "Name";
        name.dataType = "TEXT";

        SqlColumn handle;
        handle.name = "Handle";
        handle.dataType = "TEXT";

        SqlColumn limbs;
        limbs.name = "Limbs";
        limbs.dataType = "TEXT";

        SqlColumn length;
        length.name = "Length";
        length.dataType = "INTEGER";

        SqlColumn weight;
        weight.name = "Weight";
        weight.dataType = "REAL";

        SqlColumn base;
        base.name = "Base";
        base.dataType = "REAL";
        return { id, archer, name, handle, limbs, length, weight, base };
    }    
    return SqlColumns();
}
