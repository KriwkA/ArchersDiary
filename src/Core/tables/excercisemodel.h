#ifndef EXCERSICEMODEL_H
#define EXCERSICEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT ExcerciseModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID targetID READ targetID WRITE setTargetID NOTIFY targetIDChanged )
public:
    explicit ExcerciseModel( QSqlDatabase* db, QObject* parent );
    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID targetID() const { return m_targetID; }
    void setTargetID( ID targetID );

    Q_INVOKABLE bool addExcercise( const QString& name, int distance, int shotsPerSerie, int seriesCount );

signals:
    void targetIDChanged( ID id );

private:
    ID m_targetID;
};

#endif // EXCERSICEMODEL_H
