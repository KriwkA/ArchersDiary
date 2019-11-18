#pragma once

#include <bl_global.h>
#include <db/sqltablemodel.h>

class BL_SHARED_EXPORT ArchersTableModel final : public core::db::SqlTableModel
{
    Q_OBJECT
public:    
    explicit ArchersTableModel(QSqlDatabase& db, QObject* parent = nullptr);
    const core::db::SqlColumnList& getColumns() const noexcept override;

    Q_INVOKABLE bool addArcher(const QString& archerName );
};
