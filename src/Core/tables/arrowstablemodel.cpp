#include "precomp.h"
#include "arrowstablemodel.h"
#include "diarytables.h"

ArrowsTableModel::ArrowsTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerId( FAKE_ID )
{
    setTable( "Arrow" );
}

SqlTableModel::SqlColumns ArrowsTableModel::getColumns() const
{            
    auto archersModel = reinterpret_cast<SqlTableModel*>(DiaryTables::getObject()->archersModel());
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

ID ArrowsTableModel::getArcherId() const
{
    return m_archerId;
}

void ArrowsTableModel::setArcherId(ID archerId)
{
    m_archerId = archerId;
    if( m_archerId != FAKE_ID )
        setFilter(QString("Archer=%0").arg(m_archerId));
    else
        setFilter(QString(""));
}

bool ArrowsTableModel::addArrow(const QString &name, double spine, double length, double diameter)
{
    if( m_archerId != FAKE_ID )
        return insertValues({ m_archerId, name, spine, length, diameter });
    qDebug() << "Invalid archer Id";
    return false;
}
