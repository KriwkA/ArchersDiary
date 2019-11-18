#ifndef SCOPESTABLEMODEL_H
#define SCOPESTABLEMODEL_H

#include <database/sqltablemodel.h>

class BL_SHARED_EXPORT ScopesTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID bowID READ getBowID WRITE setBowID NOTIFY bowIDChanged)
public:
    explicit ScopesTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID getBowID() const { return m_bowID; }
    void setBowID(ID bowID );

    Q_INVOKABLE bool addScope(int distance, double vertical, double horizontal );

signals:
    void bowIDChanged( ID id );

private:
    ID m_bowID;

};

#endif // SCOPESTABLEMODEL_H
