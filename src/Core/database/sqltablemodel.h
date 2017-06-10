#ifndef SQLTABLE_H
#define SQLTABLE_H

#include <core_global.h>

#include <QSqlTableModel>

#include <QString>
#include <QLinkedList>
#include <QVariant>

class QSqlDatabase;

class CORESHARED_EXPORT SqlTableModel : public QSqlTableModel
{
    Q_OBJECT
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
        bool unique = false;
    };

    typedef QList< SqlColumn > SqlColumns;

    explicit SqlTableModel(QSqlDatabase *db, QObject* parent = nullptr);
    SqlTableModel(QSqlDatabase *db, const QString& name, QObject *parent = nullptr);
    SqlTableModel(QSqlDatabase *db, const QString& name, const SqlColumns& columns, QObject *parent = nullptr);
    virtual ~SqlTableModel();

    const SqlColumns& columns() const;
    void addColumn(const SqlColumn& col);
    void removeColumn(int pos);

    bool init(QString& error);

private:
    SqlColumns m_columns;
    QSqlDatabase* m_db;
    QHash<int, QByteArray> m_roles;

    bool createTable(QString& error);
    bool openDatabase(QString& error);
    bool execQuery(const QString& queryString, QString &error);


    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual bool setData(int row, const QVariant &value, int role);
};

Q_ALWAYS_INLINE const SqlTableModel::SqlColumns &SqlTableModel::columns() const
{
    return m_columns;
}

Q_ALWAYS_INLINE void SqlTableModel::addColumn(const SqlTableModel::SqlColumn &col)
{
    m_columns.append(col);
}

Q_ALWAYS_INLINE void SqlTableModel::removeColumn(int pos)
{
    if(pos < m_columns.size() && pos >= 0)
        m_columns.removeAt(pos);
}

#endif // SQLTABLE_H
