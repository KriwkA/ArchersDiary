#ifndef RECORDTABLEMODEL_H
#define RECORDTABLEMODEL_H

#include <bl_global.h>

#include <db/sqltablemodel.h>

class BL_SHARED_EXPORT RecordTableModel final : public core::db::SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(core::db::ID trainingID READ trainingID WRITE setTrainingID)
public:
    explicit RecordTableModel(QSqlDatabase& db, QObject* parent = nullptr);    
    const core::db::SqlColumnList& getColumns() const noexcept override;

    void setTrainingID(core::db::ID trainingID );
    Q_ALWAYS_INLINE core::db::ID trainingID() const { return m_trainingID; }

    Q_INVOKABLE bool addRecord(const QString& record);

signals:
    void trainingIDChanged( core::db::ID id );

private:
    core::db::ID m_trainingID;

};

#endif // RECORDTABLEMODEL_H
