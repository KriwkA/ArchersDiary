#ifndef ARROWSTABLE_H
#define ARROWSTABLE_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT ArrowsTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(long long archerID READ getArcherId WRITE setArcherId)
public:
    explicit ArrowsTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    virtual SqlColumns getColumns() const override;

    ID getArcherId() const;
    void setArcherId( ID archerId );

    Q_INVOKABLE bool addArrow( const QString& name, double spine, double length, double diameter );

private:
    long long m_archerId;
};

#endif // ARROWSTABLE_H
