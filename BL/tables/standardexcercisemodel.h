#pragma once

#include <bl_global.h>
#include <db/sqltablemodel.h>

class BL_SHARED_EXPORT StandardExcerciseModel : public core::db::SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(core::db::ID standardID READ standardID WRITE setStandardID NOTIFY standardIDChanged)
public:
    explicit StandardExcerciseModel( QSqlDatabase& db, QObject* parent = nullptr );
    const core::db::SqlColumnList& getColumns() const noexcept override;

    Q_ALWAYS_INLINE core::db::ID standardID() const { return m_standardID; }
    void setStandardID(core::db::ID standardID);

    Q_INVOKABLE bool addExcercise( core::db::ID standardID, core::db::ID excerciseID, int count = 1 );
    virtual bool createTable(QString &error) override;

    Q_INVOKABLE int excerciseCount() const;
    Q_INVOKABLE int excerciseId( int excersiceNumber ) const;

signals:
    void standardIDChanged( core::db::ID id );

private:
    bool addExcercise(const QString& standardName, const QString &excerciseName, int count = 1);    

    core::db::ID m_standardID = core::db::FAKE_ID;
};
