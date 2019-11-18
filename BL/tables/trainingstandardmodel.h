#ifndef TRAININGSTANDARDMODEL_H
#define TRAININGSTANDARDMODEL_H

#include <bl_global.h>

#include <db/sqltablemodel.h>

class BL_SHARED_EXPORT TrainingStandardModel : public core::db::SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(core::db::ID trainingID READ trainingID WRITE setTrainingID NOTIFY trainingIDChanged)

public:
    explicit TrainingStandardModel( QSqlDatabase& db, QObject* parent = nullptr );
    const core::db::SqlColumnList& getColumns() const noexcept override;
    
    Q_ALWAYS_INLINE core::db::ID trainingID() const { return m_trainingID; }
    void setTrainingID( core::db::ID trainingID );

    Q_INVOKABLE bool addStandard( core::db::ID standardID );    

signals:
    void trainingIDChanged(core::db::ID id);

private:
    core::db::ID m_trainingID;    

};

#endif // TRAININGSTANDARDMODEL_H
