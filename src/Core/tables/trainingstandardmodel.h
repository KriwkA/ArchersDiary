#ifndef TRAININGSTANDARDMODEL_H
#define TRAININGSTANDARDMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT TrainingStandardModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID trainingID READ trainingID WRITE setTrainingID NOTIFY trainingIDChanged)
public:
    explicit TrainingStandardModel( QSqlDatabase* db, QObject* parent = nullptr );
    virtual SqlColumns getColumns() const override;
    
    Q_ALWAYS_INLINE ID trainingID() const { return m_trainingID; }
    void setTrainingID( ID trainingID );

    Q_INVOKABLE bool addStandard( ID standardID );

signals:
    void trainingIDChanged( ID id );

private:
    ID m_trainingID;
};

#endif // TRAININGSTANDARDMODEL_H
