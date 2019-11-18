#include <precomp.h>
#include "sqlfield.h"

namespace core::db {

SqlField::SqlField(const QString &fieldName, const QVariant &value)
    : QSqlField( fieldName )
{
    setValue(value);
}

}
