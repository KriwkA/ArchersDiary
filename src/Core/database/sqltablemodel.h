#ifndef SQLTABLE_H
#define SQLTABLE_H

#include <core_global.h>

#include <QSqlTableModel>

#include <QString>
#include <QVariant>

class QSqlDatabase;

class SqlField;
typedef QList<SqlField> SqlFieldList;
typedef long long ID;
Q_DECLARE_METATYPE( ID )

static const ID FAKE_ID = -1;
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

        static SqlColumn createPrimaryKey( const QString name = "Id", const QString dataType = "INTEGER" );
        static SqlColumn createForeign( const QString& foreignTableName, QString datatype = "INTEGER", QString foreignField = "Id", ForeignFlags foreignFlags = ForeignFlags(OnDeleteCascade | OnUpdateCascade) );
        static SqlColumn createForeign( SqlTableModel* foreignTable, QString foreignField = "Id", ForeignFlags foreignFlags = ForeignFlags(OnDeleteCascade | OnUpdateCascade) );
    };

    typedef QList< SqlColumn > SqlColumns;
    explicit SqlTableModel(QSqlDatabase *db, QObject *parent = nullptr);
    virtual ~SqlTableModel();

    bool exist() const;
    bool init(QString& error);
    virtual SqlColumns getColumns() const = 0;
    void resetFilter();

protected:
    inline QSqlDatabase* getDataBase() const { return m_db; }
    bool insertValues(const QStringList& fieldNames, const QVariantList& values);
    bool insertValues(const QVariantList& values);
    bool insertValues(const SqlFieldList& fields);

    virtual bool createTable(QString& error);

private:
    SqlColumns m_columns;
    QSqlDatabase* m_db;
    QHash<int, QByteArray> m_roles;

    void initRoles();
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
