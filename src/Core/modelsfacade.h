#ifndef MODELSWRAPPER_H
#define MODELSWRAPPER_H

#include <core_global.h>
#include <QObject>

class QSqlDatabase;
class QSqlTableModel;
class ModelsFacaderPrivate;

class CORESHARED_EXPORT ModelsFacade : public QObject
{
    Q_OBJECT
public:
    explicit ModelsFacade(QSqlDatabase* db, QObject *parent = 0);

    QSqlTableModel* archersTable();


public slots:

signals:

private:
    Q_DISABLE_COPY( ModelsFacade )
    friend class ModelsFacaderPrivate;
    ModelsFacaderPrivate* d;
};




#endif // MODELSWRAPPER_H
