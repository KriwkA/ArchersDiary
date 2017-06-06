#ifndef MODELSWRAPPER_H
#define MODELSWRAPPER_H

#include <core_global.h>
#include <QObject>

class DiaryTablesPrivate;
class ArchersTableModel;
class ArrowsTableModel;

class CORESHARED_EXPORT DiaryTables : public QObject
{
    Q_OBJECT
public:
    explicit DiaryTables(QObject *parent = 0);

    ArchersTableModel* archersTableModel();
    ArrowsTableModel* arrowsTableModel();

signals:
    void databaseError(QString error);


private:
    Q_DISABLE_COPY( DiaryTables )
    friend class DiaryTablesPrivate;
    DiaryTablesPrivate* d;
};




#endif // MODELSWRAPPER_H
