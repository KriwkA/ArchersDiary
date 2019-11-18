#pragma once

#include <bl_global.h>
#include <memory>

#include <QDebug>
#include <cassert>

class QSqlDatabase;

namespace bl::db {

class BL_SHARED_EXPORT DbTables
{
   DbTables();
public:

   ~DbTables();

   static DbTables& Instance();


   template<typename T>
   T& getTable() const {
      static T tbl(*m_db);
      static bool initialized = [&] {
         QString error;
         tbl.init(error);
         if(error.isEmpty()) {
            return true;
         }
         qDebug() << u"SqlError" << error;
         return false;
      }();
      assert(initialized);

      return tbl;
   }

private:
   std::unique_ptr<QSqlDatabase> m_db;
};

}
