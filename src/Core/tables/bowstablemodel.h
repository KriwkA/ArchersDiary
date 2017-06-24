#ifndef BOWSTABLEMODEL_H
#define BOWSTABLEMODEL_H

#include "database/sqltablemodel.h"

class CORESHARED_EXPORT BowsTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID archerID READ getArcherId WRITE setArcherId)
public:    
    explicit BowsTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    virtual SqlColumns getColumns() const override;

    ID getArcherId() const;
    void setArcherId( ID archerId );

    Q_INVOKABLE bool addBow( const QString& name, const QString& handle, const QString& limbs, int length, double weight, double base );

private:
    ID m_archerId;
};

#endif // BOWSTABLEMODEL_H
