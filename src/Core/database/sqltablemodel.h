#ifndef SQLTABLE_H
#define SQLTABLE_H

#include <core_global.h>

#include <QSqlTableModel>

#include <QString>
#include <QVariant>

class QSqlDatabase;

class SqlField;
typedef QList<SqlField> SqlFieldList;

static const int APPEND_INDEX = -1;

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
    explicit SqlTableModel(QSqlDatabase *db, QObject *parent = nullptr);
    virtual ~SqlTableModel();

    bool init(QString& error);
    virtual SqlColumns getColumns() const = 0;

protected:
    bool insertValues(const QStringList& fieldNames, const QVariantList& values);
    bool insertValues(const QVariantList& values);
    bool insertValues(const SqlFieldList& fields);

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
    using QSqlTableModel::setData;
    Q_INVOKABLE bool setData(int row, const QVariant &value, int role);
    Q_INVOKABLE int roleFromRoleName(const QByteArray& roleName) const;    
    Q_INVOKABLE bool removeRow(int row);
};

#endif // SQLTABLE_H
