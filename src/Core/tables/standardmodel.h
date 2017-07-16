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
    Q_INVOKABLE QString standardName( ID standardId );

    int standardId( const QString& name );

protected:
    virtual bool createTable( QString &error ) override;
};

#endif // STANDARD_H
