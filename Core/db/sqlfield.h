#pragma once

#include <core_global.h>
#include <QSqlField>

namespace core::db {

class CORESHARED_EXPORT SqlField : public QSqlField
{
public:
    using QSqlField::QSqlField;    
    SqlField(const QString &fieldName, const QVariant& value);
};

typedef QList<SqlField> SqlFieldList;

}

