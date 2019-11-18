#ifndef TRAININGTABLEMODEL_H
#define TRAININGTABLEMODEL_H

#include <bl_global.h>

#include <db/sqltablemodel.h>

class BL_SHARED_EXPORT TrainingTableModel : public core::db::SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(core::db::ID archerID READ archerID WRITE setArcherID NOTIFY archerIDChanged)
    Q_PROPERTY(int shotCount READ shotCount WRITE setShotCount NOTIFY shotCountChanged)
    Q_PROPERTY(core::db::ID currentTrainingID READ currentTrainingID WRITE setCurrentTrainingID NOTIFY currentTrainingIDChanged)
public:
    explicit TrainingTableModel(QSqlDatabase& db, QObject* parent = nullptr);

    const core::db::SqlColumnList& getColumns() const noexcept override;

    virtual bool select() override;

    Q_ALWAYS_INLINE core::db::ID archerID() const { return m_archerID; }
    int shotCount() const;
    Q_ALWAYS_INLINE core::db::ID currentTrainingID() const { return m_currentTrainingID; }

    Q_INVOKABLE bool addTraining();


public slots:
    void setArcherID(core::db::ID archerID);
    void setShotCount(int shotCount);
    void setCurrentTrainingID(core::db::ID currentTrainingID)
    {
        if (m_currentTrainingID == currentTrainingID)
            return;

        m_currentTrainingID = currentTrainingID;
        emit currentTrainingIDChanged(m_currentTrainingID);
    }

signals:
    void archerIDChanged( core::db::ID id );
    void shotCountChanged( int count );
    void currentTrainingIDChanged(core::db::ID currentTrainingID);

private:
    core::db::ID m_archerID;
    core::db::ID m_currentTrainingID;

    QModelIndex currentTrainingModelIndex() const;


};

#endif // TRAININGTABLEMODEL_H
