#ifndef SHOTMODEL_H
#define SHOTMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT ShotModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID trainingStandardID READ trainingStandardID WRITE setTrainingStandardID NOTIFY trainingStandardIDChanged)
public:
    explicit ShotModel( QSqlDatabase* db, QObject* parent = nullptr );
    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID trainingStandardID() const { return m_trainingStandardID; }
    void setTrainingStandardID( const ID &trainingStandardID );

    Q_INVOKABLE bool addShot( int number, double radius, double alpha, double arrowDiameter );

signals:
    void trainingStandardIDChanged( ID id );

private:
    ID m_trainingStandardID;
};

#endif // SHOTMODEL_H
