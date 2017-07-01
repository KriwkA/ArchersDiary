#include "precomp.h"
#include "arrowstablemodel.h"
#include "diarytables.h"

ArrowsTableModel::ArrowsTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerID( FAKE_ID )
{
    setTable( "Arrow" );
}

SqlTableModel::SqlColumns ArrowsTableModel::getColumns() const
{            
    auto archersModel = DiaryTables::getTableModel( TableType::Archrers );
    if( archersModel != nullptr )
    {
        SqlColumn archer = SqlColumn::createForeign( archersModel );

        SqlColumn name;
        name.name = "Name";
        name.dataType = "TEXT";

        SqlColumn spine;
        spine.name = "Spine";
        spine.dataType = "REAL";

        SqlColumn length;
        length.name = "Length";
        length.dataType = "REAL";

        SqlColumn diameter;
        diameter.name = "Diameter";
        diameter.dataType = "REAL";

        return { archer, name, spine, length, diameter };
    }    
    return SqlColumns();
}

void ArrowsTableModel::setArcherID(ID archerID)
{
    if( m_archerID != archerID )
    {
        m_archerID = archerID;
        if( m_archerID != FAKE_ID )
            setFilter(QString("Archer=%0").arg(m_archerID));
        else
            resetFilter();
        emit archerIDChanged( m_archerID );
    }
}

bool ArrowsTableModel::addArrow(const QString &name, double spine, double length, double diameter)
{
    if( m_archerID != FAKE_ID )
        return insertValues({ m_archerID, name, spine, length, diameter });
    qDebug() << "Invalid archer Id";
    return false;
}
