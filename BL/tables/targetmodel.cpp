#include "precomp.h"
#include "targetmodel.h"

#include <QSqlField>
#include <serialization.h>

TargetModel::TargetModel(QSqlDatabase& db, QObject *parent)
    : SqlTableModel( db, parent )
{
    setTable( "Target" );
}

const core::db::SqlColumnList& TargetModel::getColumns() const noexcept
{
    using SC = core::db::SqlColumn;

    static constexpr std::array cols = {
        SC::createPrimaryKey(FieldType::ftINTEGER),
        SC(u"Name", FieldType::ftTEXT),
        SC(u"CircleCount", FieldType::ftINTEGER),
        // TODO: перегнать в один Json параметр как ftTEXT
        SC(u"Scores", FieldType::ftBLOB),
        SC(u"Radiuses", FieldType::ftBLOB),
        SC(u"Colors", FieldType::ftBLOB),
    };

    static constexpr core::utils::ContainterViewImpl res(cols);
    return static_cast<const core::db::SqlColumnList&>(res);
}

bool TargetModel::createTable( QString &error )
{
    if( SqlTableModel::createTable( error ) )
    {
        return addTarget( Target::getFitaTarget( 4.0, 10 ) ) &&
               addTarget( Target::getFitaTarget( 4.0, 5 ) ) &&
               addTarget( Target::getFitaTarget( 8.0, 10 ) ) &&
               addTarget( Target::getFitaTarget( 8.0, 6 ) ) &&
               addTarget( Target::getFitaTarget( 12.2, 10 ) );
    }
    return false;
}

bool TargetModel::addTarget(const Target &target)
{
    int count = target.circleCount;

    if( count == target.scores.size() && count == target.radiuses.size() && count == target.colors.size() )
    {
        return insertValues( {
                    target.name, count,
                    Serilization::serialize( target.scores ),
                    Serilization::serialize( target.radiuses ),
                    Serilization::serialize( target.colors )
               } );
    }

    return false;
}

int TargetModel::fitaTargetId(const QString &name)
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


QString Target::getFitaTargetName(double tenSize, int circleCount)
{
    return QString( "FITA %0cm, %1 circles" ).arg( tenSize * 10.0 ).arg( circleCount );
}

Target Target::getFitaTarget(double tenSize, int circleCount)
{
    Target target;
    target.name = getFitaTargetName( tenSize, circleCount );
    target.circleCount = circleCount;
    double radius = tenSize;
    for(int i = 0, score = 10;
        i < circleCount;
        ++i, radius += tenSize, --score)
    {
        target.colors.append( getFitaColor( score ));
        target.radiuses.append( radius );
        target.scores.append( score );
    }
    return target;
}

int Target::getFitaColor(int score)
{
    switch( score )
    {
    case 1: return 0xFFFFFF;
    case 2: return 0xFFFFFF;
    case 3: return 0x000000;
    case 4: return 0x000000;
    case 5: return 0x0000FF;
    case 6: return 0x0000FF;
    case 7: return 0xFF0000;
    case 8: return 0xFF0000;
    case 9: return 0xFFFF00;
    case 10: return 0xFFFF00;
    }
    return 0;
}
