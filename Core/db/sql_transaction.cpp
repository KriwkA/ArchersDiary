#include <precomp.h>
#include "sql_transaction.h"
#include <mutex>
#include <unordered_map>
#include <utils/hash_specialization.h>

#include <QSqlDatabase>

namespace core::db {

namespace  {
   std::unordered_map<QString, std::recursive_mutex> Locks;
}


SqlTransaction::SqlTransaction(QSqlDatabase& db) noexcept
   : m_db(db) {
   std::unique_lock lk(Locks[db.connectionName()]);
   started = m_db.transaction();
}

SqlTransaction::~SqlTransaction() {

   if(started && !commited) {
      m_db.rollback();
   }
}

bool SqlTransaction::commit() {
   if(started && !commited) {
      commited = m_db.commit();
   }
   return commited || !started;
}

}
