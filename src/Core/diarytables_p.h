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
    ArrowsTableModel* initArrowsTable();

    SqlTableModel* initTable(SqlTableModel *table, SqlTableModel **dest);

    ArchersTableModel* m_archers;
    ArrowsTableModel* m_arrows;
    QScopedPointer< QSqlDatabase > m_db;

};





#endif // MODELSWRAPPER_P_H
