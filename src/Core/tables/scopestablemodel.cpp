#include "precomp.h"
#include "scopestablemodel.h"
#include "diarytables.h"

ScopesTableModel::ScopesTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_bowID( FAKE_ID )
{
    setTable( "Scope" );
}

void ScopesTableModel::setBowID(ID bowID)
{
    if( m_bowID != bowID )
    {
        m_bowID = bowID;
        if( m_bowID >= 0 )
            setFilter(QString( "Bow=%0" ).arg(m_bowID));
        else
            setFilter(QString( "" ));
        emit bowIDChanged( m_bowID );
    }
}

bool ScopesTableModel::addScope(int distance, double vertical, double horizontal)
{
    if(m_bowID >= 0)
        return insertValues( { m_bowID, distance, vertical, horizontal } );
    qWarning() << "Invalid bow Id";
    return false;
}

SqlTableModel::SqlColumns ScopesTableModel::getColumns() const
{
    auto bowsModel = DiaryTables::getTableModel( TableType::Bows );
    if( bowsModel != nullptr )
    {
        SqlTableModel::SqlColumn bow = SqlColumn::createForeign( bowsModel );

        SqlTableModel::SqlColumn distance;
        distance.name = "Distance";
        distance.dataType = ftINTEGER;

        SqlTableModel::SqlColumn vertical;
        vertical.name = "Vertical";
        vertical.dataType = ftREAL;

        SqlTableModel::SqlColumn horizontal;
        horizontal.name = "Horizontal";
        horizontal.dataType = ftREAL;

        return { bow, distance, vertical, horizontal };
    }   
    return SqlColumns();
}
