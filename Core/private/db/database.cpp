#include "database.h"
#include <QSqlDatabase>

namespace core::db_private {

QSqlDatabase& get_db() {
   static QSqlDatabase db = []{
      QSqlDatabase db(QSqlDatabase::addDatabase("QSQLITE", "db_core.sqlite"));
      db.setDatabaseName("db_core.sqlite");
      if(db.open()) {
         return db;
      }
      throw std::runtime_error( "Data base: db not opened" );
   }();

   return db;

}


}

