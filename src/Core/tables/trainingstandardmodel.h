#ifndef TRAININGSTANDARDMODEL_H
#define TRAININGSTANDARDMODEL_H

#include <database/sqltablemodel.h>

class TrainingStandardModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID trainingID READ trainingID WRITE setTrainingID)
public:
    explicit TrainingStandardModel( QSqlDatabase* db, QObject* parent = nullptr );
    virtual SqlColumns getColumns() const override;
    
    Q_ALWAYS_INLINE ID trainingID() const { return m_trainingID; }
    void setTrainingID( ID trainingID );

    Q_INVOKABLE bool addStandard( ID standardID );

private:
    ID m_trainingID;
};

#endif // TRAININGSTANDARDMODEL_H
