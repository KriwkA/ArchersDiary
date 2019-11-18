#include <precomp.h>
#include "hash_specialization.h"




#define IMPL_HASH_SPECIALIZATION(Type) \
   size_t std::hash<Type>::operator()(const Type& v) const noexcept

IMPL_HASH_SPECIALIZATION(QString) {
   return qHash(v);
}

IMPL_HASH_SPECIALIZATION(QDate) {
   return std::hash<decltype(v.toJulianDay())>()(v.toJulianDay());
}

IMPL_HASH_SPECIALIZATION(QUuid) {
   return qHash(v);
}