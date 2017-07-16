#include "precomp.h"
#include "standardexcercisemodel.h"
#include "diarytables.h"
#include "excercisemodel.h"
#include "standardmodel.h"

StandardExcerciseModel::StandardExcerciseModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel( db, parent )
    , m_standardID( FAKE_ID )
{
    setTable( "StandardExcersice" );
}

SqlTableModel::SqlColumns StandardExcerciseModel::getColumns() const
{
    auto standards = this->standards();
    auto excercises = this->excercises();
    if( !( standards == nullptr || excercises == nullptr ) ) {
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

bool StandardExcerciseModel::addExcercise(ID standardID, ID excerciseID, int count)
{
    for( int i = 0; i < count; ++i )
        if( !insertValues( { standardID, excerciseID } ) )
            return false;
    return true;
}

bool StandardExcerciseModel::createTable(QString &error)
{
    if( SqlTableModel::createTable( error ) )
    {
        const char* juniorsM1Name = "60m, 50m, 40m, 30m (144 shots)";
        const char* mensM1Name = "90m, 70m, 50m, 30m (144 shots)";
        const char* womensM1Name = "70m, 60m, 50m, 30m (144 shots)";
        return  addExcercise( "12m (30 shots)", "12m (30 shots)" ) &&
                addExcercise( "18m (30 shots)", "18m (30 shots)" ) &&
                addExcercise( "30m (36 shots)", "30m (36 shots)" ) &&
                addExcercise( "50m (36 shots)", "50m (36 shots)" ) &&
                addExcercise( "60m (36 shots)", "60m (36 shots)" ) &&
                addExcercise( "70m (36 shots)", "70m (36 shots)" ) &&
                addExcercise( "90m (36 shots)", "90m (36 shots)" ) &&

                addExcercise( "12m (60 shots)", "12m (30 shots)" ) &&
                addExcercise( "18m (60 shots)", "18m (30 shots)" ) &&
                addExcercise( "30m (72 shots)", "30m (36 shots)" ) &&
                addExcercise( "50m (72 shots)", "50m (36 shots)" ) &&
                addExcercise( "60m (72 shots)", "60m (36 shots)" ) &&
                addExcercise( "70m (72 shots)", "70m (36 shots)" ) &&
                addExcercise( "90m (72 shots)", "90m (36 shots)" ) &&

                addExcercise( juniorsM1Name, "60m (36 shots)" ) &&
                addExcercise( juniorsM1Name, "50m (36 shots)" ) &&
                addExcercise( juniorsM1Name, "40m (36 shots)" ) &&
                addExcercise( juniorsM1Name, "30m (36 shots)" ) &&

                addExcercise( mensM1Name, "90m (36 shots)" ) &&
                addExcercise( mensM1Name, "70m (36 shots)" ) &&
                addExcercise( mensM1Name, "50m (36 shots)" ) &&
                addExcercise( mensM1Name, "30m (36 shots)" ) &&

                addExcercise( womensM1Name, "70m (36 shots)" ) &&
                addExcercise( womensM1Name, "60m (36 shots)" ) &&
                addExcercise( womensM1Name, "50m (36 shots)" ) &&
                addExcercise( womensM1Name, "30m (36 shots)" );
    }
    return false;
}

bool StandardExcerciseModel::addExcercise(const QString &standardName, const QString& excerciseName, int count )
{
    auto standards = this->standards();
    auto excercises = this->excercises();
    if( !( standards == nullptr || excercises == nullptr ) )
        return addExcercise( standards->standardId( standardName ), excercises->excerciseID( excerciseName ), count );
    return false;
}

StandardModel *StandardExcerciseModel::standards() const
{
    return static_cast< StandardModel* >( DiaryTables::getTableModel( TableType::Standards ) );
}

ExcerciseModel *StandardExcerciseModel::excercises() const
{
    return static_cast< ExcerciseModel* >( DiaryTables::getTableModel( TableType::Excercises ) );
}
