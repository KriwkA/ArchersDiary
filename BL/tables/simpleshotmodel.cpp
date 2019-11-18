#include <precomp.h>
#include "simpleshotmodel.h"
#include "trainingstandardmodel.h"
#include "dbtables.h"


SimpleShotModel::SimpleShotModel(QSqlDatabase& db, QObject *parent)
    : BaseShotModel( db, parent )
{
    setTable( "SimpleShotModel" );
}


const core::db::SqlColumnList& SimpleShotModel::getColumns() const noexcept
{
    constexpr auto init_cols = +[]{
        using SC = core::db::SqlColumn;
        return std::array{
                SC::createPrimaryKey(FieldType::ftINTEGER),
                SC::createForeign(bl::db::DbTables::Instance().getTable<TrainingStandardModel>()),
                SC(u"Number", FieldType::ftINTEGER),
                SC(u"Round", FieldType::ftINTEGER),
                SC(u"Score", FieldType::ftINTEGER),
        };
    };

    // TODO: constexpr
    static auto cols = init_cols();
    static core::utils::ContainterViewImpl res(cols);
    return res;
}


bool SimpleShotModel::setShot(int number, int score)
{
    if( trainingStandardID() != core::db::FAKE_ID )
    {
        if( shotExists( number ) )
            return updateShot( number, score );
        return addShot( number, score );
    }
    return false;
}

int SimpleShotModel::shot(int number) const
{
    if( trainingStandardID() != core::db::FAKE_ID )
    {
        QSqlRecord rec = recByShotNumber( number );
        if( rec.contains( "Score" ) )
            return rec.value( "Score" ).toInt();
    }
    return -1;
}

bool SimpleShotModel::addShot(int number, int score)
{    
    return insertValues( { trainingStandardID(), number, round(), score } );
}

bool SimpleShotModel::shotExists(int number)
{
    return !recByShotNumber( number ).isEmpty();
}

bool SimpleShotModel::updateShot(int number, int score)
{
    int row;
    QSqlRecord shotRec = recByShotNumber( number, &row );

    if( !shotRec.isEmpty() )    
        return setData( row, score, roleFromRoleName( "Score" ) );

    return false;
}

QSqlRecord SimpleShotModel::recByShotNumber(int number, int *row) const
{
    QSqlRecord rec;
    for(int i = 0; i < rowCount(); ++i) {
        rec = record( i );
        if( rec.field("Number").value().toInt() == number && rec.field("Round").value().toInt() == round() ) {
            if( row != nullptr )
                *row = i;
            return rec;
        }
    }
    if( row != nullptr )
        *row = -1;
    return QSqlRecord();
}
