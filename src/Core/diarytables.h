#ifndef MODELSWRAPPER_H
#define MODELSWRAPPER_H

#include <core_global.h>
#include <QObject>

class DiaryTablesPrivate;
class SqlTableModel;

class CORESHARED_EXPORT DiaryTables : public QObject
{
    Q_OBJECT
public:
    explicit DiaryTables(QObject *parent = 0);

    SqlTableModel* archersTableModel(QString& error);


private:
    Q_DISABLE_COPY( DiaryTables )
    friend class DiaryTablesPrivate;
    DiaryTablesPrivate* d;

    static SqlTableModel* archersTable();
};




#endif // MODELSWRAPPER_H
