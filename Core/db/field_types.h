#pragma once

#include <QStringView>

enum class FieldType : short {
   ftNULL,
   ftINTEGER,
   ftREAL,
   ftTEXT,
   ftBLOB,
   ftUUID,
   ftDATE,
   ftDATE_TIME,
};

constexpr QStringView ToString(FieldType type) noexcept {
   constexpr QStringView integer = u"INTEGER";
   constexpr QStringView text = u"TEXT";
   constexpr QStringView real = u"REAL";
   constexpr QStringView blob = u"BLOB";
   constexpr QStringView null = u"NULL";


   switch (type) {
   case FieldType::ftNULL: return null;
   case FieldType::ftINTEGER: return integer;
   case FieldType::ftREAL: return real;
   case FieldType::ftTEXT: return text;
   case FieldType::ftBLOB: return blob;
   case FieldType::ftUUID: return text;
   case FieldType::ftDATE: return integer;
   case FieldType::ftDATE_TIME: return integer;
   }

   return QStringView(u"ErrorFieldType");
}
