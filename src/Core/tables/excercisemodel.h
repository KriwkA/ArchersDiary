#ifndef EXCERSICEMODEL_H
#define EXCERSICEMODEL_H

#include <database/sqltablemodel.h>

class ExcerciseModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID targetID READ targetID WRITE setTargetID)
public:
    explicit ExcerciseModel( QSqlDatabase* db, QObject* parent );
    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID targetID() const { return m_targetID; }
    void setTargetID( ID targetID );

    Q_INVOKABLE bool addExcercise( const QString& name, int distance, int shotsPerSerie, int seriesCount );

private:
    ID m_targetID;
};

#endif // EXCERSICEMODEL_H
