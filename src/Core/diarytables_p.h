#ifndef MODELSWRAPPER_P_H
#define MODELSWRAPPER_P_H

#include <core_global.h>
#include <QScopedPointer>

class DiaryTables;
class QSqlTableModel;
class QSqlDatabase;

//tables
class ArchersTableModel;


class DiaryTablesPrivate
{
    friend class DiaryTables;
    DiaryTables* q;

private:
    DiaryTablesPrivate(DiaryTables* qPtr);


    ArchersTableModel *initArchersTable(QString &error);
    ArchersTableModel* createArchersTable();
    ArchersTableModel* m_archers;

    QScopedPointer< QSqlDatabase > m_db;

};





#endif // MODELSWRAPPER_P_H
