#ifndef SQLTABLE_H
#define SQLTABLE_H

#include <core_global.h>

#include <QString>
#include <QLinkedList>
#include <QVariant>

class QSqlDatabase;

class CORESHARED_EXPORT SqlTable
{
public:
    enum Type
    {
        NONE = 0,
        PRIMARY_KEY,
        FOREIGN_KEY,
    };

    enum ForeignFlags
    {
        NoFlags = 0x0000,
        OnDeleteCascade = 0x0001,
        OnUpdateCascade = 0x0002,
    };

    struct SqlColumn
    {
        QString name;
        QString dataType;
        Type type = NONE;
        ForeignFlags foreignFlags = NoFlags;
        QString foreignTable;
        QString foreingField;
    };

    typedef QList< SqlColumn > SqlColumns;

    SqlTable();
    SqlTable(const QString& name);
    SqlTable(const QString& name, const SqlColumns& columns);
    ~SqlTable();

    QString name() const;
    void setName(const QString& name);

    const SqlColumns& columns() const;
    void addColumn(const SqlColumn& col);
    void removeColumn(int pos);

    bool init(QSqlDatabase* db, QString& error);
    bool insertValues(QSqlDatabase* db, const QVariantList& values, QString& error);
    bool insertValues(QSqlDatabase* db, const QStringList& colNames, const QVariantList& values, QString& error);

private:
    QString m_name;
    SqlColumns m_columns;

    bool createTable(QSqlDatabase* db, QString& error);
    bool openDatabase(QSqlDatabase* db, QString& error);
    static bool execQuery(QSqlDatabase *db, const QString& queryString, QString &error);
};

Q_ALWAYS_INLINE QString SqlTable::name() const
{
    return m_name;
}

Q_ALWAYS_INLINE void SqlTable::setName(const QString &name)
{
    m_name = name;
}

Q_ALWAYS_INLINE const SqlTable::SqlColumns &SqlTable::columns() const
{
    return m_columns;
}

Q_ALWAYS_INLINE void SqlTable::addColumn(const SqlTable::SqlColumn &col)
{
    m_columns.append(col);
}

Q_ALWAYS_INLINE void SqlTable::removeColumn(int pos)
{
    if(pos < m_columns.size() && pos >= 0)
        m_columns.removeAt(pos);
}

#endif // SQLTABLE_H
