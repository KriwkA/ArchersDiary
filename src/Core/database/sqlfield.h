#ifndef SQLFIELD_H
#define SQLFIELD_H

#include <QSqlField>

class SqlField : public QSqlField
{
public:
    using QSqlField::QSqlField;
    SqlField();
    SqlField(const QString &fieldName, const QVariant& value);
};

typedef QList<SqlField> SqlFieldList;

#endif // SQLFIELD_H
