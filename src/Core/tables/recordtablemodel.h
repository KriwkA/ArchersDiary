#ifndef RECORDTABLEMODEL_H
#define RECORDTABLEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT RecordTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID trainingID READ getTrainingId WRITE setTrainingID)
public:
    explicit RecordTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    virtual SqlColumns getColumns() const override;

    inline ID getTrainingId() const { return m_trainingId; }
    void setTrainingID( ID trainingId );

    Q_INVOKABLE bool addRecord(const QString& record);

private:
    ID m_trainingId;
};

#endif // RECORDTABLEMODEL_H
