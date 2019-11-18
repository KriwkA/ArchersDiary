#ifndef EXCERSICEMODEL_H
#define EXCERSICEMODEL_H

#include <db/sqltablemodel.h>


#include <bl_global.h>

class BL_SHARED_EXPORT ExcerciseModel : public core::db::SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(core::db::ID targetID READ targetID WRITE setTargetID NOTIFY targetIDChanged )
public:
    explicit ExcerciseModel( QSqlDatabase& db, QObject* parent = nullptr );
    const core::db::SqlColumnList& getColumns() const noexcept override;

    Q_ALWAYS_INLINE core::db::ID targetID() const { return m_targetID; }
    void setTargetID( core::db::ID targetID );

    Q_INVOKABLE bool addExcercise( const QString& name, int distance, int shotsPerSerie, int seriesCount );

    int excerciseID( const QString& name ) const;
    Q_INVOKABLE QString excerciseName( core::db::ID excersiceID ) const;
    Q_INVOKABLE int shotPerSerie( core::db::ID excersiceID ) const;
    Q_INVOKABLE int seriesCount( core::db::ID excersiceID ) const;

protected:
    virtual bool createTable(QString &error) override;

signals:
    void targetIDChanged( core::db::ID id );

private:
    bool addExcercise( const QString& targetName, const QString& excersiceName, int distance, int shotsPerSerie, int seriesCount );
    bool addExcercise( core::db::ID targetID, const QString& excersiceName, int distance, int shotsPerSerie, int seriesCount );


    core::db::ID m_targetID = core::db::FAKE_ID;
};

#endif // EXCERSICEMODEL_H
