#include <precomp.h>
#include "excercisemodel.h"
#include "targetmodel.h"
#include "dbtables.h"

ExcerciseModel::ExcerciseModel(QSqlDatabase& db, QObject *parent)
    : SqlTableModel( db, parent )    
{
    setTable( "Excersice" );
}

const core::db::SqlColumnList& ExcerciseModel::getColumns() const noexcept
{
    constexpr auto init_cols = +[]{
        using SC = core::db::SqlColumn;
        return std::array{
            SC::createPrimaryKey(FieldType::ftINTEGER),
            SC::createForeign(bl::db::DbTables::Instance().getTable<TargetModel>()),
            SC(u"Name", FieldType::ftTEXT),
            SC(u"Distance", FieldType::ftINTEGER),
            SC(u"ShotsPerSerie", FieldType::ftINTEGER),
            SC(u"SeriesCount", FieldType::ftINTEGER),
        };
    };

    // TODO: constexpr
    static auto cols = init_cols();
    static core::utils::ContainterViewImpl res(cols);
    return res;
}

void ExcerciseModel::setTargetID(core::db::ID targetID)
{
    if( m_targetID != targetID )
    {
        m_targetID = targetID;
        if( m_targetID != core::db::FAKE_ID )
            setFilter( QString("Target=%0").arg(m_targetID) );
        else
            resetFilter();
        emit targetIDChanged( m_targetID );
    }
}

bool ExcerciseModel::addExcercise(const QString &name, int distance, int shotsPerSerie, int seriesCount)
{
    if( m_targetID != core::db::FAKE_ID )
        return addExcercise( m_targetID, name, distance, shotsPerSerie, seriesCount );
    return false;
}

int ExcerciseModel::excerciseID(const QString& name) const
{
    int rows = rowCount();
    QSqlRecord rec;
    for(int i = 0; i < rows; ++i) {
        rec = record(i);
        if( rec.field("Name").value().toString() == name )
            return rec.field("Id").value().toInt();
    }
    return core::db::FAKE_ID;
}

QString ExcerciseModel::excerciseName(core::db::ID excersiceID) const
{
    QSqlRecord rec = recordById(excersiceID);
    if(rec.contains("Name"))
        return rec.field("Name").value().toString();
    return "Unknown excercise";
}

int ExcerciseModel::shotPerSerie(core::db::ID excersiceID) const
{
    QSqlRecord rec = recordById( excersiceID );
    if( rec.contains( "ShotsPerSerie") ) {
        return rec.field("ShotsPerSerie").value().toInt();
    }
    return 0;
}

int ExcerciseModel::seriesCount(core::db::ID excersiceID) const
{
    QSqlRecord rec = recordById( excersiceID );
    if( rec.contains( "SeriesCount") ) {
        return rec.field("SeriesCount").value().toInt();
    }
    return 0;
}

bool ExcerciseModel::createTable(QString &error)
{
    if( SqlTableModel::createTable( error ) ) {
        return  addExcercise( Target::getFitaTargetName( 4, 10 ), "12m (30 shots)", 12, 3, 10 ) &&
                addExcercise( Target::getFitaTargetName( 4, 5 ), "18m (30 shots)", 18, 3, 10 ) &&
                addExcercise( Target::getFitaTargetName( 8, 6 ), "30m (36 shots)", 30, 6, 6 )  &&
                addExcercise( Target::getFitaTargetName( 8, 6 ), "40m (36 shots)", 40, 6, 6 )  &&
                addExcercise( Target::getFitaTargetName( 8, 6 ), "50m (36 shots)", 50, 6, 6 )  &&
                addExcercise( Target::getFitaTargetName( 12.2, 10 ), "60m (36 shots)", 60, 6, 6 ) &&
                addExcercise( Target::getFitaTargetName( 12.2, 10 ), "70m (36 shots)", 70, 6, 6 ) &&
                addExcercise( Target::getFitaTargetName( 12.2, 10 ), "90m (36 shots)", 90, 6, 6 );
    }
    return false;
}

bool ExcerciseModel::addExcercise(const QString &targetName, const QString &excersiceName, int distance, int shotsPerSerie, int seriesCount)
{
    auto& pTargets = bl::db::DbTables::Instance().getTable<TargetModel>();
    core::db::ID targetID = pTargets.fitaTargetId( targetName );
    if( targetID != core::db::FAKE_ID )
        return addExcercise( targetID, excersiceName, distance, shotsPerSerie, seriesCount );
    return false;
}

bool ExcerciseModel::addExcercise(core::db::ID targetID, const QString &excersiceName, int distance, int shotsPerSerie, int seriesCount)
{
    return insertValues( { targetID, excersiceName, distance, shotsPerSerie, seriesCount } );
}
