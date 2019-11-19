#pragma once

#include <bl_global.h>
#include <db/sqltablemodel.h>

// TODO переделать в единственную можель для выстрелов с Json данными об упражнении. Скорее всего нужно удалить и унести в TrainingTableModel
class BL_SHARED_EXPORT BaseShotModel : public core::db::SqlTableModel
{
    Q_OBJECT
public:
    Q_PROPERTY(core::db::ID trainingID READ trainingID WRITE setTrainingID NOTIFY trainingIDChanged)
    Q_PROPERTY(int round READ round WRITE setRound NOTIFY roundChanged)

    explicit BaseShotModel( QSqlDatabase& db, QObject* parent = nullptr );

    Q_ALWAYS_INLINE core::db::ID trainingID() const { return m_trainingID; }
    Q_ALWAYS_INLINE int round() const { return m_round; }

public slots:
    void setTrainingID(const core::db::ID &trainingID );
    void setRound(int round);    

signals:
    void trainingIDChanged( core::db::ID ID );
    void roundChanged(int round);

protected:
    virtual void resetFilter();
    void updateFilter();

private:
    core::db::ID m_trainingID;
    int m_round;
};
