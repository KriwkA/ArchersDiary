#ifndef SQLFIELD_H
#define SQLFIELD_H

#include <bl_global.h>
#include <QSqlField>

class BL_SHARED_EXPORT SqlField : public QSqlField
{
public:
    using QSqlField::QSqlField;
    SqlField(const QString &fieldName, const QVariant& value);
};

typedef QList<SqlField> SqlFieldList;

#endif // SQLFIELD_H
