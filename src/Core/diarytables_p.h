#ifndef MODELSWRAPPER_P_H
#define MODELSWRAPPER_P_H

#include <core_global.h>
#include <QScopedPointer>

class DiaryTables;
class QSqlTableModel;
class SqlTableModel;
class QSqlDatabase;


class DiaryTablesPrivate
{
    friend class DiaryTables;
    DiaryTables* q;

private:
    DiaryTablesPrivate(DiaryTables* qPtr);


    SqlTableModel *initArchersTable(QString &error);
    SqlTableModel* createArchersTable();
    SqlTableModel* m_archers;

    QScopedPointer< QSqlDatabase > m_db;

};





#endif // MODELSWRAPPER_P_H
