#include <precomp.h>
#include "shotmodel.h"

#include "dbtables.h"
#include "trainingstandardmodel.h"

ShotModel::ShotModel(QSqlDatabase& db, QObject *parent)
    : BaseShotModel( db, parent )
{
    setTable( "ShotModel" );
}

const core::db::SqlColumnList& ShotModel::getColumns() const noexcept
{
    constexpr auto init_cols = +[]{
        using SC = core::db::SqlColumn;
        return std::array{
                SC::createPrimaryKey(FieldType::ftINTEGER),
                SC::createForeign(bl::db::DbTables::Instance().getTable<TrainingStandardModel>()),
                SC(u"Number", FieldType::ftINTEGER),
                SC(u"Round", FieldType::ftINTEGER),
                SC(u"Radius", FieldType::ftREAL),
                SC(u"Alpha", FieldType::ftREAL),
                SC(u"ArrowDiameter", FieldType::ftREAL)
        };
    };

    // TODO: constexpr
    static auto cols = init_cols();
    static core::utils::ContainterViewImpl res(cols);
    return res;
}

bool ShotModel::addShot(int number, double radius, double alpha, double arrowDiameter)
{
    if( trainingStandardID() != core::db::FAKE_ID )
        return insertValues( { trainingStandardID(), number, round(), radius, alpha, arrowDiameter } );
    return false;
}
