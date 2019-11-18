#ifndef STANDARD_H
#define STANDARD_H

#include <bl_global.h>

#include <db/sqltablemodel.h>

class BL_SHARED_EXPORT StandardModel : public core::db::SqlTableModel
{
    Q_OBJECT
public:
    explicit StandardModel( QSqlDatabase& db, QObject* parent = nullptr );
    const core::db::SqlColumnList& getColumns() const noexcept override;

    Q_INVOKABLE bool addStandard( const QString& name );
    Q_INVOKABLE QString standardName( core::db::ID standardId );

    int standardId( const QString& name );

protected:
    virtual bool createTable( QString &error ) override;
};

#endif // STANDARD_H
