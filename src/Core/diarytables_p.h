#ifndef MODELSWRAPPER_P_H
#define MODELSWRAPPER_P_H

#include <core_global.h>
#include <QScopedPointer>

class DiaryTables;
class QSqlTableModel;
class QSqlDatabase;

//tables
class SqlTableModel;
class ArchersTableModel;
class ArrowsTableModel;


class DiaryTablesPrivate
{
    friend class DiaryTables;
    DiaryTables* q;

private:
    DiaryTablesPrivate(DiaryTables* qPtr);


    ArchersTableModel* initArchersTable();
    ArchersTableModel* m_archers;

    ArrowsTableModel* initArrowsTable();
    ArrowsTableModel* m_arrows;

    SqlTableModel* initTable(SqlTableModel *table, SqlTableModel **dest);

    QScopedPointer< QSqlDatabase > m_db;

};





#endif // MODELSWRAPPER_P_H
