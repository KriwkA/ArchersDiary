#include <precomp.h>
#include "standardexcercisemodel.h"
#include "excercisemodel.h"
#include "standardmodel.h"

#include "dbtables.h"

StandardExcerciseModel::StandardExcerciseModel(QSqlDatabase& db, QObject *parent)
    : SqlTableModel( db, parent )
{
    setTable( "StandardExcersice" );
}

const core::db::SqlColumnList& StandardExcerciseModel::getColumns() const noexcept
{
    constexpr auto init_cols = +[]{
        using SC = core::db::SqlColumn;
        return std::array{
            SC::createPrimaryKey(FieldType::ftINTEGER),
            SC::createForeign(bl::db::DbTables::Instance().getTable<StandardModel>()),
            SC::createForeign(bl::db::DbTables::Instance().getTable<ExcerciseModel>()),
        };
    };

    // TODO: constexpr
    static auto cols = init_cols();
    static core::utils::ContainterViewImpl res(cols);
    return res;
}

void StandardExcerciseModel::setStandardID(core::db::ID standardID)
{
    if( m_standardID != standardID )
    {
        m_standardID = standardID;
        if( m_standardID != core::db::FAKE_ID )
            setFilter( QString("Standard=%0").arg( m_standardID ));
        else
            resetFilter();
        select();
        emit standardIDChanged( m_standardID );
    }
}

bool StandardExcerciseModel::addExcercise(core::db::ID standardID, core::db::ID excerciseID, int count)
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
                addExcercise( "12m (60 shots)", "12m (30 shots)" ) &&
                addExcercise( "18m (60 shots)", "18m (30 shots)" ) &&
                addExcercise( "18m (60 shots)", "18m (30 shots)" ) &&
                addExcercise( "30m (72 shots)", "30m (36 shots)" ) &&
                addExcercise( "30m (72 shots)", "30m (36 shots)" ) &&
                addExcercise( "50m (72 shots)", "50m (36 shots)" ) &&
                addExcercise( "50m (72 shots)", "50m (36 shots)" ) &&
                addExcercise( "60m (72 shots)", "60m (36 shots)" ) &&
                addExcercise( "60m (72 shots)", "60m (36 shots)" ) &&
                addExcercise( "70m (72 shots)", "70m (36 shots)" ) &&
                addExcercise( "70m (72 shots)", "70m (36 shots)" ) &&
                addExcercise( "90m (72 shots)", "90m (36 shots)" ) &&
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

int StandardExcerciseModel::excerciseCount() const
{
    return rowCount();
}

int StandardExcerciseModel::excerciseId(int excersiceNumber) const
{
    if( excersiceNumber < excerciseCount() ) {
        bool goodCast;
        core::db::ID id = data( index( excersiceNumber, 0 ), roleFromRoleName( "Excersice" ) ).toInt(&goodCast);
        if( goodCast )
            return static_cast<int>(id);
    }
    return core::db::FAKE_ID;
}

bool StandardExcerciseModel::addExcercise(const QString &standardName, const QString& excerciseName, int count )
{
    auto& tbls = bl::db::DbTables::Instance();
    return addExcercise( tbls.getTable<StandardModel>().standardId( standardName ), tbls.getTable<ExcerciseModel>().excerciseID( excerciseName ), count );
}
