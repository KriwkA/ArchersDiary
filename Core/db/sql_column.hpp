#pragma once

#include "field_types.h"
#include <utils/container_view.hpp>

namespace core::db {

struct SqlColumn
{
   enum KeyType
   {
      ktNoKey = 0,
      ktPrimaryKey,
      ktForeighKey,
   };

   enum ForeignFlags
   {
      ffNoFlags = 0x0000,
      ffOnDeleteCascade = 0x0001,
      ffOnUpdateCascade = 0x0002,
   };

   static constexpr QStringView default_id_field = u"Id";
   static constexpr ForeignFlags defaul_ff = ForeignFlags(ffOnDeleteCascade | ffOnUpdateCascade);


   constexpr SqlColumn() = default;

   constexpr SqlColumn( const QStringView& colName, FieldType ft ) noexcept
      : name(colName), fieldType(ft) {}

   QStringView name;
   FieldType fieldType = FieldType::ftNULL;
   KeyType keyType = ktNoKey;
   ForeignFlags foreignFlags = ffNoFlags;
   QStringView foreignTable;
   QStringView foreingField;
   bool unique = false;

   static constexpr SqlColumn createPrimaryKey(FieldType ft, const QStringView name = default_id_field) noexcept {
      SqlColumn col(name, ft);
      col.keyType = ktPrimaryKey;
      return col;
   }

   static constexpr SqlColumn createForeign( const QStringView& foreignTableName, FieldType ft,
                                             const QStringView& foreignField = default_id_field, ForeignFlags foreignFlags = defaul_ff ) noexcept {
      SqlColumn col(foreignTableName, ft);
      col.keyType = ktForeighKey;
      col.foreignFlags = foreignFlags;
      col.foreignTable = foreignTableName;
      col.foreingField = foreignField;
      return col;
   }

   template<typename ForeignTbl>
   static constexpr SqlColumn createForeign(const ForeignTbl& foreignTable,
                                            const QStringView& foreignField = default_id_field,
                                            ForeignFlags foreignFlags = defaul_ff) noexcept {
      for(auto& c : foreignTable.getColumns()) {
         if(c.name == foreignField) {
            return createForeign(foreignTable.tableName(), c.fieldType, foreignField, foreignFlags);
         }
      }
      return SqlColumn();
   }
};

using SqlColumnList = utils::ContainterView<SqlColumn>;

}
