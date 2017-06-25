#include "precomp.h"
#include "standardexcercisemodel.h"

StandardExcerciseModel::StandardExcerciseModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_standardID( FAKE_ID )
{
    setTable( "StandardExcersice" );
}

SqlTableModel::SqlColumns StandardExcerciseModel::getColumns() const
{
    auto standards = reinterpret_cast<SqlTableModel*>(DiaryTables::getObject()->standardModel());
    auto excercises = reinterpret_cast<SqlTableModel*>(DiaryTables::getObject()->excersiceModel());
    if( standards != nullptr && excercises != nullptr ) {
        SqlColumn standard = SqlColumn::createForeign( standards );
        SqlColumn excersice = SqlColumn::createForeign( excercises );
        return { standard, excersice };
    }
    return SqlColumns();
}

void StandardExcerciseModel::setStandardID(ID standardID)
{
    m_standardID = standardID;
    if( m_standardID != FAKE_ID )
        setFilter( QString("Standard=%0").arg( m_standardID ));
    else
        resetFilter();
}

bool StandardExcerciseModel::addExcercise(ID excerciseID)
{
    if( m_standardID != FAKE_ID )
        return insertValues( { m_standardID, excerciseID } );
    return false;
}
