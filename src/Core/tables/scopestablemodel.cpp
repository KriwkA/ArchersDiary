#include "precomp.h"
#include "scopestablemodel.h"

ScopesTableModel::ScopesTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_bowId(-1)
{
    setTable( "Scope" );
}

void ScopesTableModel::setBowId(ID bowId)
{
    m_bowId = bowId;
    if( m_bowId >= 0 )
        setFilter(QString( "Bow=%0" ).arg(m_bowId));
    else
        setFilter(QString( "" ));
}

bool ScopesTableModel::addScope(int distance, double vertical, double horizontal)
{
    if(m_bowId >= 0)    
        return insertValues( { m_bowId, distance, vertical, horizontal } );
    qWarning() << "Invalid bow Id";
    return false;
}


SqlTableModel::SqlColumns ScopesTableModel::getColumns() const
{
    SqlTableModel::SqlColumn bow;
    bow.name = "Bow";
    bow.dataType = "INTEGER";
    bow.type = SqlTableModel::FOREIGN_KEY;
    bow.foreignFlags = ForeignFlags(OnDeleteCascade | OnUpdateCascade);
    bow.foreignTable = "Bow";
    bow.foreingField = "Id";

    SqlTableModel::SqlColumn distance;
    distance.name = "Distance";
    distance.dataType = "INTEGER";

    SqlTableModel::SqlColumn vertical;
    vertical.name = "Vertical";
    vertical.dataType = "REAL";

    SqlTableModel::SqlColumn horizontal;
    horizontal.name = "Horizontal";
    horizontal.dataType = "REAL";

    return { bow, distance, vertical, horizontal };
}
