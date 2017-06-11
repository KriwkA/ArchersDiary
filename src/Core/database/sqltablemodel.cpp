#include "precomp.h"
#include "sqltablemodel.h"


SqlTableModel::SqlTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, QString(), parent)
{
}

SqlTableModel::SqlTableModel(QSqlDatabase *db, const QString &name, QObject *parent)
    : SqlTableModel(db, name, SqlColumns(), parent )
{
}

SqlTableModel::SqlTableModel(QSqlDatabase *db, const QString &name, const SqlTableModel::SqlColumns &columns, QObject *parent)
    : QSqlTableModel(parent)
    , m_columns(columns)
    , m_db( db )
{
    setTable(name);
    setEditStrategy( QSqlTableModel::OnFieldChange );
}

SqlTableModel::~SqlTableModel()
{

}

bool SqlTableModel::init(QString &error)
{
    if( openDatabase(error) && createTable(error) )
        return true;
    return false;
}

void SqlTableModel::insertAllValues(const QStringList &fieldNames, const QStringList &values)
{
    QString fields = !fieldNames.isEmpty() ? QString("( %1 )").arg( fieldNames.join(", ")) : "";
    QString allValues = QString("( %1 )").arg( values.join(", "));
    QString queryString = QString("INSERT INTO %0 %1 VALUES %2;").arg( tableName() ).arg(fields).arg(allValues);

    QSqlQuery query;
    if(!query.exec(queryString))
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }
}

void SqlTableModel::insertAllValues(const QStringList &values)
{
    insertAllValues(QStringList(), values);
}

bool SqlTableModel::createTable(QString &error)
{
    QString queryString = QString("CREATE TABLE IF NOT EXISTS %0").arg( tableName() );
    queryString.reserve( queryString.length() * (m_columns.count() + 1) * 2 );

    QStringList fields;
    m_roles.clear();

    for(const auto& col : m_columns)
    {
        QString fieldStr = QString("%0 %1").arg( col.name ).arg( col.dataType );

        if(col.unique)
            fieldStr.append(" UNIQUE");

        switch (col.type) {
        case PRIMARY_KEY:
                fieldStr.append(" PRIMARY KEY");
            break;
        case FOREIGN_KEY:
            fieldStr.append(QString(" REFERENCES %0(%1)").arg(col.foreignTable).arg(col.foreingField));
            if(col.foreignFlags & OnDeleteCascade)
                fieldStr.append(" ON DELETE CASCADE");
            if(col.foreignFlags & OnUpdateCascade)
                fieldStr.append(" ON UPDATE CASCADE");
            break;
        default:
            break;
        }

        fields.append(fieldStr);
        m_roles.insert(Qt::UserRole + m_roles.size() + 1, col.name.toLatin1());
    }
    if(fields.size())
        queryString.append(QString(" ( %0 )").arg(fields.join(", ")));

    queryString.append(';');
    return execQuery(queryString, error);
}

bool SqlTableModel::openDatabase(QString &error)
{    
    if( m_db->isOpen() || m_db->open() )
        return true;
    error = "Database not opened: " + m_db->lastError().text();
    return false;
}

bool SqlTableModel::execQuery(const QString &queryString, QString& error)
{
    QSqlQuery query( *m_db );
    if(query.exec(queryString))
        return true;
    error = query.lastError().text();
    return false;
}


QVariant SqlTableModel::data(const QModelIndex &index, int role) const
{
    if(m_roles.contains(role))
    {
        QString name( m_roles[role] );
        QVariant val = record(index.row()).field(name).value();
        return val;
    }
    return QSqlTableModel::data(index, role);
}

QHash<int, QByteArray> SqlTableModel::roleNames() const
{
    return m_roles;
}


bool SqlTableModel::setData(int row, const QVariant &value, int role)
{
    if(m_roles.contains(role))
    {
        const QString name( m_roles[role] );
        const auto it = std::find_if(m_columns.begin(), m_columns.end(), [ name ](const SqlColumn& col){ return col.name == name; } );
        if( it != m_columns.end() )
        {
            const int col = std::distance(m_columns.begin(), it);
            const QModelIndex index = createIndex(row, col);
            if( QSqlTableModel::setData(index, value, Qt::EditRole) )
            {
                emit dataChanged(index, index, QVector<int>() << role);                
                return true;
            } else {
                qDebug() << lastError().text();
            }
        }
    }
    return false;
}

int SqlTableModel::roleFromRoleName(const QByteArray &roleName) const
{
    for(auto roleIt = m_roles.cbegin(); roleIt != m_roles.cend(); ++roleIt) {
        QByteArray arr = roleIt.value();
        if(roleIt.value() == roleName)
            return roleIt.key();
    }
    return -1;
}


bool SqlTableModel::removeRows(int row, int count)
{    
    if( QSqlTableModel::removeRows(row, count) ) {
        select();
        return true;
    }
    return false;
}
