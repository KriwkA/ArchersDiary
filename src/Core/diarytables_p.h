#ifndef MODELSWRAPPER_P_H
#define MODELSWRAPPER_P_H

#include <QScopedPointer>
#include <tables/alltables.h>

class DiaryTables;

class DiaryTablesPrivate
{
    friend class DiaryTables;
    DiaryTables* q;

private:
    DiaryTablesPrivate(DiaryTables* qPtr);

    ArchersTableModel* initArchersTable();
    ArrowsTableModel* initArrowsTable();
    BowsTableModel* initBowsTable();
    ScopesTableModel* initScopesTableModel();

    template<typename Table>
    Q_ALWAYS_INLINE Table* initTable(Table* &dest)
    {
        if( dest != nullptr ) {
            return dest;
        }

        dest = new Table( m_db.data(), q );

        if( dest != nullptr ) {
            QString error;
            if( dest->init( error ) )
                return dest;

            qDebug() << error;
//            emit q->databaseError( error );
            delete dest;
        }                

        return dest = nullptr;
    }

    ArchersTableModel* m_archers;
    ArrowsTableModel* m_arrows;
    BowsTableModel* m_bows;
    ScopesTableModel* m_scopes;

    QScopedPointer< QSqlDatabase > m_db;

};





#endif // MODELSWRAPPER_P_H
