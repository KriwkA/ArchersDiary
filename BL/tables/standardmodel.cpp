#include "precomp.h"
#include "standardmodel.h"

#include <QSqlField>

StandardModel::StandardModel(QSqlDatabase& db, QObject *parent)
    : SqlTableModel( db, parent )
{
    setTable( "Standard" );
}

const core::db::SqlColumnList& StandardModel::getColumns() const noexcept
{
    using SC = core::db::SqlColumn;

    static constexpr std::array cols = {
        SC::createPrimaryKey(FieldType::ftINTEGER),
        SC(u"Name", FieldType::ftTEXT)
    };
    static constexpr core::utils::ContainterViewImpl res(cols);

    return static_cast<const core::db::SqlColumnList&>(res);
}

bool StandardModel::addStandard(const QString &name)
{
    return insertValues( QVariantList{ name } );
}

QString StandardModel::standardName(core::db::ID standardId)
{
    int rows = rowCount();
    QSqlRecord rec;
    bool goodCast = false;
    for(int i = 0; i < rows; ++i) {
        rec = record(i);
        core::db::ID id = rec.field("Id").value().toInt( &goodCast );
        if( goodCast && id == standardId )
            return rec.field("Name").value().toString();
    }
    return "Unknown standard";
}

int StandardModel::standardId( const QString &name )
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

bool StandardModel::createTable(QString &error)
{
    if( SqlTableModel::createTable( error ) )
    {
        return  addStandard( "12m (30 shots)" ) &&
                addStandard( "18m (30 shots)" ) &&
                addStandard( "30m (36 shots)" ) &&
                addStandard( "50m (36 shots)" ) &&
                addStandard( "60m (36 shots)" ) &&
                addStandard( "70m (36 shots)" ) &&
                addStandard( "90m (36 shots)" ) &&

                addStandard( "12m (60 shots)") &&
                addStandard( "18m (60 shots)") &&
                addStandard( "30m (72 shots)") &&
                addStandard( "50m (72 shots)") &&
                addStandard( "60m (72 shots)") &&
                addStandard( "70m (72 shots)") &&
                addStandard( "90m (72 shots)") &&

                addStandard( "60m, 50m, 40m, 30m (144 shots)") &&
                addStandard( "90m, 70m, 50m, 30m (144 shots)") &&
                addStandard( "70m, 60m, 50m, 30m (144 shots)");
    }
    return false;
}
