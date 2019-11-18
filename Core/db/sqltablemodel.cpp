#include <precomp.h>
#include "sqltablemodel.h"
#include "sqlfield.h"
#include "version_table.h"

namespace core::db {

SqlTableModel::SqlTableModel(QSqlDatabase& db, QObject *parent)
   : QSqlTableModel(parent, db)
   , m_db(db)
{
   setEditStrategy( QSqlTableModel::OnFieldChange );
}

SqlTableModel::~SqlTableModel()
{
}

bool SqlTableModel::exist() const
{   
   return m_db.tables().contains(tableName());
}

bool SqlTableModel::init(QString &error)
{
   m_columns = &getColumns();
   if( exist() || createTable( error ) )
   {
      if(useVersion()) {
         if (auto old = VersionTable::version(*this)) {
            if(*old != version()) {
               convert(*old);
               VersionTable::updateVersion(*this);
            }
         } else {
            VersionTable::updateVersion(*this);
         }
      }

      initRoles();
      return true;
   }
   return false;
}

void SqlTableModel::resetFilter()
{
   auto tr = startTransaction();
   setFilter( "" );
   tr.commit();
}

bool SqlTableModel::insertValues(const QStringViewList &fieldNames, const QVariantList &values)
{
   const int valuesCount = values.size();
   if( fieldNames.size() == valuesCount )
   {
      SqlFieldList fields;
      SqlField field;
      for(int i = 0; i < valuesCount; ++i)
      {
         field.setName( fieldNames[i].toString() );
         field.setValue( values[i] );
         fields.append( field);
      }
      return insertValues( fields );
   }
   return false;
}

bool SqlTableModel::insertValues(const QVariantList &values)
{
   QStringViewList names;
   for(const auto& col : *m_columns)
   {
      if(col.keyType != SqlColumn::ktPrimaryKey || col.fieldType != FieldType::ftINTEGER) {
         names.append( col.name );
      }
   }
   return insertValues( names, values );
}

bool SqlTableModel::insertValues(const SqlFieldList &fields)
{
   QSqlRecord newRec;
   for(const auto& field : fields)
      newRec.append( field );
   auto tr = startTransaction();
   return insertRecord( APPEND_INDEX, newRec ) && tr.commit();
}

bool SqlTableModel::createTable(QString &error)
{   
   QStringList fields;

   for(const auto& col : *m_columns)
   {
      QString fieldStr = QString("%0 %1").arg( col.name ).arg( ToString(col.fieldType) );

      if(col.unique)
         fieldStr.append(" UNIQUE");

      switch (col.keyType) {
      case SqlColumn::ktPrimaryKey:
         fieldStr.append(" PRIMARY KEY");
         break;
      case SqlColumn::ktForeighKey:
         fieldStr.append(QString(" REFERENCES %0(%1)").arg(col.foreignTable).arg(col.foreingField));
         if(col.foreignFlags & SqlColumn::ffOnDeleteCascade)
            fieldStr.append(" ON DELETE CASCADE");
         if(col.foreignFlags & SqlColumn::ffOnUpdateCascade)
            fieldStr.append(" ON UPDATE CASCADE");
         break;
      default:
         break;
      }

      fields.append(fieldStr);
   }

   const QString& name = tableName();

   QString queryString = QString("CREATE TABLE IF NOT EXISTS %0").arg( name );
   queryString.reserve( queryString.length() * (static_cast<int>(m_columns->size()) + 1) * 2 );

   if(fields.size())
      queryString.append(QString(" ( %0 )").arg(fields.join(", ")));

   if( execQuery(queryString, error) ) {
      setTable( name );
      return true;
   }

   qDebug() << error;

   return false;
}

QSqlRecord SqlTableModel::recordById(core::db::ID id) const
{
   SqlTransaction tr(m_db);
   int rows = rowCount();
   QSqlRecord rec;
   bool goodCast = false;
   for(int i = 0; i < rows; ++i) {
      rec = record(i);
      if( rec.field("Id").value().toInt( &goodCast ) == id && goodCast )
         return rec;
   }

   return QSqlRecord();
}

void SqlTableModel::initRoles()
{
   m_roles.clear();
   for(const auto& col : *m_columns){
      m_roles.insert(Qt::UserRole + m_roles.size() + 1, col.name.toLatin1());
   }
}

bool SqlTableModel::execQuery(const QString &queryString, QString& error)
{   
   SqlTransaction tr(m_db);
   QSqlQuery query( m_db );
   if(query.exec(queryString))
      return m_db.commit();
   error = query.lastError().text();
   return false;
}

QVariant SqlTableModel::data(const QModelIndex &index, int role) const
{
   SqlTransaction tr(m_db);
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
   SqlTransaction tr(m_db);
   QList<int> l;
   if(m_roles.contains(role))
   {
      const QString name( m_roles[role] );
      const auto it = std::find_if(m_columns->begin(), m_columns->end(), [ name ](const SqlColumn& col){ return col.name == name; } );
      if( it != m_columns->end() )
      {
         const int col = static_cast<int>(m_columns->index(it));
         const QModelIndex index = createIndex(row, col);
         if( QSqlTableModel::setData(index, value, Qt::EditRole) && tr.commit() )
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
   SqlTransaction tr(m_db);
   if( QSqlTableModel::removeRow(row) && tr.commit() ) {
      select();
      return true;
   }
   return false;
}

}
