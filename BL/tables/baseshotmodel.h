#pragma once

#include <bl_global.h>
#include <db/sqltablemodel.h>


class BL_SHARED_EXPORT BaseShotModel : public core::db::SqlTableModel
{
    Q_OBJECT
public:
    Q_PROPERTY(core::db::ID trainingStandardID READ trainingStandardID WRITE setTrainingStandardID NOTIFY trainingStandardIDChanged)
    Q_PROPERTY(int round READ round WRITE setRound NOTIFY roundChanged)

    explicit BaseShotModel( QSqlDatabase& db, QObject* parent = nullptr );

    Q_ALWAYS_INLINE core::db::ID trainingStandardID() const { return m_trainingStandardID; }
    Q_ALWAYS_INLINE int round() const { return m_round; }

public slots:
    void setTrainingStandardID( const core::db::ID &trainingStandardID );
    void setRound(int round);    

signals:
    void trainingStandardIDChanged( core::db::ID ID );
    void roundChanged(int round);

protected:
    virtual void resetFilter();
    void updateFilter();

private:
    core::db::ID m_trainingStandardID;
    int m_round;
};
