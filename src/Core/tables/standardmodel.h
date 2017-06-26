#ifndef STANDARD_H
#define STANDARD_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT StandardModel : public SqlTableModel
{
    Q_OBJECT
public:
    explicit StandardModel( QSqlDatabase* db, QObject* parent = nullptr );
    virtual SqlColumns getColumns() const override;

    Q_INVOKABLE bool addStandard( const QString& name );
};

#endif // STANDARD_H
