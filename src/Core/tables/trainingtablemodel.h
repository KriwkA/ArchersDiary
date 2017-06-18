#ifndef TRAININGTABLEMODEL_H
#define TRAININGTABLEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT TrainingTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(long long archerID READ getArcherId WRITE setArcherId)
public:
    explicit TrainingTableModel(QSqlDatabase* db, QObject* parent = nullptr);

    virtual SqlColumns getColumns() const override;

    inline ID getArcherId() const { return m_archerId; }
    void setArcherId(ID archerId);

    Q_INVOKABLE bool addTraining();

private:
    ID m_archerId;
};

#endif // TRAININGTABLEMODEL_H
