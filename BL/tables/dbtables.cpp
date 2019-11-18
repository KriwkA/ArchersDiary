#include "dbtables.h"
#include <QSqlDatabase>
#include <QSqlQuery>


namespace bl::db {

DbTables::DbTables()
   : m_db(std::make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE", "bl_database.sqlite")))
{
    m_db->setDatabaseName("bl_database.sqlite");
    if(m_db->open()) {
        QSqlQuery query(*m_db);
        if( query.exec("PRAGMA foreign_keys = ON;") ) {            
            return;
        }
        throw std::runtime_error( "Data base: foreing keys wasn`t on" );
    }
    throw std::runtime_error( "Data base: db not opened" );
}

DbTables::~DbTables() {
}

DbTables& DbTables::Instance()
{
   static DbTables inst;
   return inst;
}


}
