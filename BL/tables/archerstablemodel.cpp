#include "precomp.h"
#include "archerstablemodel.h"

ArchersTableModel::ArchersTableModel(QSqlDatabase& db, QObject* parent)
    : core::db::SqlTableModel(db, parent)
{
    setTable( "Archer" );
}

const core::db::SqlColumnList& ArchersTableModel::getColumns() const noexcept
{
    using SC = core::db::SqlColumn;

    static constexpr std::array cols = {
        SC::createPrimaryKey(FieldType::ftINTEGER),
        SC(u"Name", FieldType::ftTEXT)
    };

    static constexpr core::utils::ContainterViewImpl res(cols);
    return static_cast<const core::db::SqlColumnList&>(res);
}

bool ArchersTableModel::addArcher(const QString &archerName)
{    
    return insertValues( QVariantList{ archerName } );
}
