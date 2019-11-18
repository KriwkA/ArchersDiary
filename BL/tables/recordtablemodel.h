#ifndef RECORDTABLEMODEL_H
#define RECORDTABLEMODEL_H

#include <database/sqltablemodel.h>

class BL_SHARED_EXPORT RecordTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID trainingID READ trainingID WRITE setTrainingID)
public:
    explicit RecordTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    virtual SqlColumns getColumns() const override;

    void setTrainingID(ID trainingID );
    Q_ALWAYS_INLINE ID trainingID() const { return m_trainingID; }

    Q_INVOKABLE bool addRecord(const QString& record);

signals:
    void trainingIDChanged( ID id );

private:
    ID m_trainingID;
};

#endif // RECORDTABLEMODEL_H
