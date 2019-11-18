#include "version_table.h"
#include <private/db/database.h>
#include <array>

namespace core::db {



VersionTable::VersionTable(QObject* parent)
   : SqlTableModel(core::db_private::get_db(), parent)
{
   setTable("DbTableVersion");
}

const SqlColumnList& VersionTable::getColumns() const noexcept
{
   using SC = core::db::SqlColumn;

   static constexpr std::array cols = {
      SC::createPrimaryKey(FieldType::ftTEXT, u"TableName"),
      SC(u"Major", FieldType::ftINTEGER),
      SC(u"Minor", FieldType::ftINTEGER),
   };

   static constexpr core::utils::ContainterViewImpl res(cols);

   return static_cast<const core::db::SqlColumnList&>(res);
}

VersionTable& VersionTable::Instance()
{
   static VersionTable tbl;
   static bool initialized = [&] {
      QString error;
      tbl.init(error);
      if(error.isEmpty()) {
         return true;
      }
      qDebug() << u"SqlError" << error;
      return false;
   }();
   assert(initialized);

   return tbl;
}

std::optional<SqlTableModel::Version> VersionTable::version(const SqlTableModel& m)
{
   std::optional<Version> vers;

   auto& tbl = Instance();

   SqlTransaction tr(core::db_private::get_db());

   QSqlQuery query(core::db_private::get_db());
   query.exec(QString("SELECT [Major], [Minor] FROM [%1] WHERE [TableName]='%2'").arg(tbl.tableName()).arg(m.tableName()));
   if(query.next()) {
      vers = Version{
                query.value(0).toUInt(),
                query.value(1).toUInt()
             };
   }

   return vers;
}

void VersionTable::updateVersion(const SqlTableModel& m)
{
   SqlTransaction tr(core::db_private::get_db());
   auto v = m.version();
   auto& tbl = Instance();
   QSqlQuery query(core::db_private::get_db());
   query.exec(QString("INSERT OR REPLACE INTO [%1] ([TableName], [Major], [Minor]) VALUES ('%2', %3, %4)").arg(tbl.tableName()).arg(m.tableName()).arg(v.major).arg(v.minor));
   tr.commit();
}


}
