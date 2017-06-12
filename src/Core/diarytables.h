#ifndef MODELSWRAPPER_H
#define MODELSWRAPPER_H

#include <core_global.h>
#include <QObject>

class DiaryTablesPrivate;
class ArchersTableModel;
class ArrowsTableModel;
class BowsTableModel;
class ScopesTableModel;

class CORESHARED_EXPORT DiaryTables : public QObject
{
    Q_OBJECT
public:
    explicit DiaryTables(QObject *parent = 0);      
    DiaryTables(DiaryTables&& move);
    void operator=(DiaryTables&& move);
    virtual ~DiaryTables();

    ArchersTableModel* archersTableModel();
    ArrowsTableModel* arrowsTableModel();
    BowsTableModel *bowsTableModel();
    ScopesTableModel *scopesTableModel();

signals:
    void databaseError(QString error);

private:
    Q_DISABLE_COPY( DiaryTables )
    friend class DiaryTablesPrivate;
    DiaryTablesPrivate* d;
};




#endif // MODELSWRAPPER_H
