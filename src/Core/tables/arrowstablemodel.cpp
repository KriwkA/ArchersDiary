#include "precomp.h"
#include "arrowstablemodel.h"

ArrowsTableModel::ArrowsTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerId(-1)
{
    setTable( "Arrow" );
}

SqlTableModel::SqlColumns ArrowsTableModel::getColumns() const
{    
    ArchersTableModel archers( getDataBase() );
    QString error;
    if( archers.init(error) )
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
    qCritical() << error;
    return SqlColumns();
}

ID ArrowsTableModel::getArcherId() const
{
    return m_archerId;
}

void ArrowsTableModel::setArcherId(ID archerId)
{
    m_archerId = archerId;
    if(m_archerId >= 0)
        setFilter(QString("Archer=%0").arg(m_archerId));
    else
        setFilter(QString(""));
}

bool ArrowsTableModel::addArrow(const QString &name, double spine, double length, double diameter)
{
    if(m_archerId >= 0)
        return insertValues({ m_archerId, name, spine, length, diameter });
    qDebug() << "Invalid archer Id";
    return false;
}
