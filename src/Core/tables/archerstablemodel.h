#ifndef ARCHERSTABLEMODEL_H
#define ARCHERSTABLEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT ArchersTableModel : public SqlTableModel
{
    Q_OBJECT
public:    
    explicit ArchersTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    static SqlTableModel::SqlColumns getColumns();

public slots:
    void addArcher(const QString& archerName );
};

#endif // ARCHERSTABLEMODEL_H