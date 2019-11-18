#pragma once

#include <core_global.h>
#include <functional>


class QString;
class QDate;
class QUuid;

#define DECL_HASH_SPECIALIZATION(Type) \
   template<> struct CORESHARED_EXPORT std::hash<Type> { \
      size_t operator()(const Type& v) const noexcept; \
   };


DECL_HASH_SPECIALIZATION(QString)
DECL_HASH_SPECIALIZATION(QDate)
DECL_HASH_SPECIALIZATION(QUuid)

#undef DECL_HASH_SPECIALIZATION
