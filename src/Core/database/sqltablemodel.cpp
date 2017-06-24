#include "precomp.h"
#include "sqltablemodel.h"

SqlTableModel::SqlTableModel(QSqlDatabase *db, QObject *parent)
    : QSqlTableModel(parent)   
    , m_db( db )
{
    setEditStrategy( QSqlTableModel::OnRowChange );
}

SqlTableModel::~SqlTableModel()
{
}

bool SqlTableModel::init(QString &error)
{
    m_columns = getColumns();
    if( openDatabase(error) && createTable(error) )
        return true;
    return false;
}

bool SqlTableModel::insertValues(const QStringList &fieldNames, const QVariantList &values)
{
    const int valuesCount = values.size();
    if( fieldNames.size() == valuesCount )
    {
        SqlFieldList fields;
        SqlField field;
        for(int i = 0; i < valuesCount; ++i)
        {
            field.setName( fieldNames[i] );
            field.setValue( values[i] );
            fields.append( field);
        }
        return insertValues( fields );
    }
    return false;
}

bool SqlTableModel::insertValues(const QVariantList &values)
{
    QStringList names;
    for(const auto& col : m_columns)
    {
        if(col.type != PRIMARY_KEY)
            names.append( col.name );
    }
    return insertValues( names, values );
}

bool SqlTableModel::insertValues(const SqlFieldList &fields)
{
    QSqlRecord newRec;
    for(const auto& field : fields)
        newRec.append( field );
    return insertRecord( APPEND_INDEX, newRec );
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
    for( auto roleIt = m_roles.cbegin(); roleIt != m_roles.cend(); ++roleIt ) {
        QByteArray arr = roleIt.value();
        if( roleIt.value() == roleName )
            return roleIt.key();
    }
    return -1;
}


bool SqlTableModel::removeRow(int row)
{    
    if( QSqlTableModel::removeRow(row) ) {
        select();
        return true;
    }
    return false;
}

SqlTableModel::SqlColumn SqlTableModel::SqlColumn::createPrimaryKey(const QString name, const QString dataType)
{
    SqlColumn primaryCol;
    primaryCol.name = name;
    primaryCol.dataType = dataType;
    primaryCol.type = PRIMARY_KEY;
    return primaryCol;
}

SqlTableModel::SqlColumn SqlTableModel::SqlColumn::createForeign(const QString &foreignTableName, QString dataType, QString foreignField, SqlTableModel::ForeignFlags foreignFlags)
{
    SqlColumn col;
    col.name = foreignTableName;
    col.dataType = dataType;
    col.type = FOREIGN_KEY;
    col.foreignFlags = foreignFlags;
    col.foreignTable = foreignTableName;
    col.foreingField = foreignField;
    return col;
}

SqlTableModel::SqlColumn SqlTableModel::SqlColumn::createForeign(SqlTableModel *foreignTable, QString foreignField, SqlTableModel::ForeignFlags foreignFlags)
{
    if( foreignTable != nullptr )
    {
        for( const auto& col : foreignTable->getColumns() )
        {
            if( col.name == foreignField )
                return createForeign( foreignTable->tableName(), col.dataType, foreignField, foreignFlags);
        }
    }
    return SqlColumn();
}
