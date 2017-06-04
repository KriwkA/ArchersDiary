#ifndef MODELSWRAPPER_H
#define MODELSWRAPPER_H

#include <core_global.h>
#include <QObject>

class QSqlDatabase;
class QSqlTableModel;
class ModelsFacadePrivate;
class SqlTable;

class CORESHARED_EXPORT ModelsFacade : public QObject
{
    Q_OBJECT
public:
    explicit ModelsFacade(QSqlDatabase* db, QObject *parent = 0);

    QSqlTableModel* archersTableModel(QString& error);
    static SqlTable archersTable();


public slots:

signals:

private:
    Q_DISABLE_COPY( ModelsFacade )
    friend class ModelsFacadePrivate;
    ModelsFacadePrivate* d;
};




#endif // MODELSWRAPPER_H
