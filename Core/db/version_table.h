#pragma once
#include "sqltablemodel.h"

#include <optional>

namespace core::db {

class VersionTable : SqlTableModel
{
   explicit VersionTable(QObject *parent = nullptr);
   const SqlColumnList& getColumns() const noexcept override;

   bool useVersion() const noexcept override { return false; }

   static VersionTable& Instance();

public:

   static std::optional<Version> version(const SqlTableModel& m);
   static void updateVersion(const SqlTableModel& m);

};

}
