#ifndef ARROWSTABLE_H
#define ARROWSTABLE_H

#include <core_global.h>
#include <database/sqltablemodel.h>

class ArrowsTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(long long archerID READ getArcherId WRITE setArcherId)
public:
    explicit ArrowsTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    static SqlColumns getColumns();

    long long getArcherId() const;
    void setArcherId( long long archerId );

public slots:
    void addArrow( const QString& name, double spine, double length, double diameter );

private:
    long long m_archerId;
};

#endif // ARROWSTABLE_H
