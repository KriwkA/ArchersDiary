#ifndef ARCHERSTABLEMODEL_H
#define ARCHERSTABLEMODEL_H

#include <database/sqltablemodel.h>

class BL_SHARED_EXPORT ArchersTableModel : public SqlTableModel
{
    Q_OBJECT
public:    
    explicit ArchersTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    virtual SqlColumns getColumns() const override;

    Q_INVOKABLE bool addArcher(const QString& archerName );
};

#endif // ARCHERSTABLEMODEL_H
