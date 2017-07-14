#include "precomp.h"
#include "standardexcercisemodel.h"
#include "diarytables.h"

StandardExcerciseModel::StandardExcerciseModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_standardID( FAKE_ID )
{
    setTable( "StandardExcersice" );
}

SqlTableModel::SqlColumns StandardExcerciseModel::getColumns() const
{
    auto standards = DiaryTables::getTableModel( TableType::Standards );
    auto excercises = DiaryTables::getTableModel( TableType::Excercises );
    if( standards != nullptr && excercises != nullptr ) {
        SqlTableModel::SqlColumn id = SqlColumn::createPrimaryKey();
        SqlColumn standard = SqlColumn::createForeign( standards );
        SqlColumn excersice = SqlColumn::createForeign( excercises );
        return { id, standard, excersice };
    }
    return SqlColumns();
}

void StandardExcerciseModel::setStandardID(ID standardID)
{
    if( m_standardID != standardID )
    {
        m_standardID = standardID;
        if( m_standardID != FAKE_ID )
            setFilter( QString("Standard=%0").arg( m_standardID ));
        else
            resetFilter();
        emit standardIDChanged( m_standardID );
    }
}

bool StandardExcerciseModel::addExcercise(ID excerciseID)
{
    if( m_standardID != FAKE_ID )
        return insertValues( { m_standardID, excerciseID } );
    return false;
}
