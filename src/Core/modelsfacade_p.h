#ifndef MODELSWRAPPER_P_H
#define MODELSWRAPPER_P_H

#include <core_global.h>

class ModelsFacade;
class QSqlTableModel;
class SqlTable;
class QSqlDatabase;


class ModelsFacaderPrivate
{
    friend class ModelsFacade;
    ModelsFacade* q;

private:
    ModelsFacaderPrivate(ModelsFacade* qPtr, QSqlDatabase* db);

    QSqlTableModel* archersTable();
    QSqlTableModel* initArchersTable();

    QSqlTableModel* initTable(QSqlTableModel **tableModel, SqlTable &table);

    QSqlDatabase* m_db;
    QSqlTableModel* m_archers;

};

inline QSqlTableModel *ModelsFacaderPrivate::archersTable()
{
    if( m_archers != nullptr)
        return m_archers;
    return m_archers = initArchersTable();
}



#endif // MODELSWRAPPER_P_H
