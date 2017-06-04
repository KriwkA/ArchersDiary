#ifndef MODELSWRAPPER_P_H
#define MODELSWRAPPER_P_H

#include <core_global.h>

class ModelsFacade;
class QSqlTableModel;
class SqlTable;
class QSqlDatabase;


class ModelsFacadePrivate
{
    friend class ModelsFacade;
    ModelsFacade* q;

private:
    ModelsFacadePrivate(ModelsFacade* qPtr, QSqlDatabase* db);

    QSqlTableModel* archersTable(QString &error);
    QSqlTableModel* initArchersTable(QString &error);

    QSqlTableModel* initTable(QSqlTableModel **tableModel, SqlTable (*getTable)(void), QString &error);

    QSqlDatabase* m_db;
    QSqlTableModel* m_archers;

};

inline QSqlTableModel *ModelsFacadePrivate::archersTable(QString &error)
{
    if( m_archers != nullptr)
        return m_archers;
    return m_archers = initArchersTable(error);
}



#endif // MODELSWRAPPER_P_H
