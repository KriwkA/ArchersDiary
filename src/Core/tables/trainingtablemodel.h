#ifndef TRAININGTABLEMODEL_H
#define TRAININGTABLEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT TrainingTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID archerID READ archerID WRITE setArcherID NOTIFY archerIDChanged)
public:
    explicit TrainingTableModel(QSqlDatabase* db, QObject* parent = nullptr);

    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID archerID() const { return m_archerID; }
    void setArcherID(ID archerID);

    Q_INVOKABLE bool addTraining();

signals:
    void archerIDChanged( ID id );

private:
    ID m_archerID;
};

#endif // TRAININGTABLEMODEL_H
