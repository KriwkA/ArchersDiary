#include "precomp.h"
#include "sqlfield.h"

SqlField::SqlField(const QString &fieldName, const QVariant &value)
    : QSqlField( fieldName )
{
    setValue(value);
}
