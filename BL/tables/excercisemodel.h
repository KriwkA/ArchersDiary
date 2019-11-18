#ifndef EXCERSICEMODEL_H
#define EXCERSICEMODEL_H

#include <database/sqltablemodel.h>

class TargetModel;

class BL_SHARED_EXPORT ExcerciseModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID targetID READ targetID WRITE setTargetID NOTIFY targetIDChanged )
public:
    explicit ExcerciseModel( QSqlDatabase* db, QObject* parent );
    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID targetID() const { return m_targetID; }
    void setTargetID( ID targetID );

    Q_INVOKABLE bool addExcercise( const QString& name, int distance, int shotsPerSerie, int seriesCount );

    int excerciseID( const QString& name ) const;
    Q_INVOKABLE QString excerciseName( ID excersiceID ) const;
    Q_INVOKABLE int shotPerSerie( ID excersiceID ) const;
    Q_INVOKABLE int seriesCount( ID excersiceID ) const;

protected:
    virtual bool createTable(QString &error) override;

signals:
    void targetIDChanged( ID id );

private:
    bool addExcercise( const QString& targetName, const QString& excersiceName, int distance, int shotsPerSerie, int seriesCount );
    bool addExcercise( ID targetID, const QString& excersiceName, int distance, int shotsPerSerie, int seriesCount );

    TargetModel* targetModel() const;

    ID m_targetID;


};

#endif // EXCERSICEMODEL_H
