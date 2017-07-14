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
    if( m_archerId != archerId )
    {
        m_archerId = archerId;
        if( m_archerId != FAKE_ID )
            setFilter(QString("Archer=%0").arg(m_archerId));
        else
            resetFilter();
        emit archerIdChanged( m_archerId );
    }
}

bool BowsTableModel::addBow(const QString &name, const QString &handle, const QString &limbs /*, int length, double weight, double base */ )
{
    if( m_archerId !=  FAKE_ID )
        return insertValues( { m_archerId, name, handle, limbs /*, length, weight, base */ } );

    qDebug() << "Invalid archer Id";
    return false;
}


SqlTableModel::SqlColumns BowsTableModel::getColumns() const
{    
    auto archersModel = DiaryTables::getTableModel( TableType::Archrers );
    if( archersModel != nullptr )
    {
        SqlColumn id = SqlColumn::createPrimaryKey();
        SqlColumn archer = SqlColumn::createForeign( archersModel );

        SqlColumn name;
        name.name = "Name";
        name.dataType = ftTEXT;

        SqlColumn handle;
        handle.name = "Handle";
        handle.dataType = ftTEXT;

        SqlColumn limbs;
        limbs.name = "Limbs";
        limbs.dataType = ftTEXT;

        //        SqlColumn length;
        //        length.name = "Length";
        //        length.dataType = ftINTEGER;

        //        SqlColumn weight;
        //        weight.name = "Weight";
        //        weight.dataType = ftREAL;

        //        SqlColumn base;
        //        base.name = "Base";
        //        base.dataType = ftREAL;
        return { id, archer, name, handle, limbs, /* length, weight, base */ };
    }
    return SqlColumns();
}
