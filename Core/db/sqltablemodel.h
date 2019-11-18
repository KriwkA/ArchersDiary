#pragma once

#include <core_global.h>
#include "sql_column.hpp"
#include "sql_transaction.h"


#include <QSqlTableModel>

#include <QString>
#include <QVariant>

class QSqlDatabase;

using QStringViewList = QList<QStringView>;

namespace core::db {

class SqlField;
typedef QList<SqlField> SqlFieldList;
typedef long long ID;

constexpr ID FAKE_ID = -1;
constexpr int APPEND_INDEX = -1;

class CORESHARED_EXPORT SqlTableModel : public QSqlTableModel
{
   Q_OBJECT
public:

   struct Version {
      uint32_t major = 1;
      uint32_t minor = 0;

      inline constexpr bool operator==(const Version& v) const noexcept {
         return major == v.major && minor == v.minor;
      }

      inline constexpr bool operator!=(const Version& v) const noexcept {
         return !operator==(v);
      }
   };

   explicit SqlTableModel(QSqlDatabase& db, QObject *parent = nullptr);
   ~SqlTableModel() override;

   bool exist() const;
   bool init( QString& error );
   virtual const SqlColumnList& getColumns() const noexcept = 0;

   SqlTransaction startTransaction() {
      return SqlTransaction(m_db);
   }

   virtual bool useVersion() const noexcept { return true; }
   virtual Version version() const noexcept { return Version(); }

   virtual void convert(const Version& /*from*/) {}


protected:
   inline QSqlDatabase& getDataBase() const { return m_db; }
   bool insertValues(const QStringViewList& fieldNames, const QVariantList& values);
   bool insertValues(const QVariantList& values);
   bool insertValues(const SqlFieldList& fields);

   virtual bool createTable(QString& error);
   virtual void resetFilter();

   QSqlRecord recordById( core::db::ID id ) const;

private:
   const SqlColumnList* m_columns;
   QSqlDatabase& m_db;
   QHash<int, QByteArray> m_roles;

   void initRoles();
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



}

Q_DECLARE_METATYPE( core::db::ID )
