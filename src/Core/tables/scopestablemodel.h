#ifndef SCOPESTABLEMODEL_H
#define SCOPESTABLEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT ScopesTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(long long bowId READ getBowId WRITE setBowId)
public:
    explicit ScopesTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    virtual SqlColumns getColumns() const override;

    inline ID getBowId() const { return m_bowId; }
    void setBowId(ID bowId );

    Q_INVOKABLE bool addScope(int distance, double vertical, double horizontal );

private:
    ID m_bowId;

};

#endif // SCOPESTABLEMODEL_H
