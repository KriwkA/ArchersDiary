#pragma once
#include <core_global.h>

class QSqlDatabase;

namespace core::db {

class CORESHARED_EXPORT SqlTransaction {
   QSqlDatabase& m_db;
   bool commited = false;
   bool started = false;

public:
   explicit SqlTransaction(QSqlDatabase& db) noexcept;
   ~SqlTransaction();

   bool commit();

private:
   SqlTransaction(SqlTransaction&&) = delete;
   SqlTransaction(const SqlTransaction&) = delete;

   SqlTransaction& operator=(SqlTransaction&&) = delete;
   SqlTransaction& operator=(const SqlTransaction&) = delete;
};

}
