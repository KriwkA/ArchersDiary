#ifndef SHOTMODEL_H
#define SHOTMODEL_H

#include <database/sqltablemodel.h>

class ShotModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID trainingStandardID READ trainingStandardID WRITE setTrainingStandardID)
public:
    explicit ShotModel( QSqlDatabase* db, QObject* parent = nullptr );
    virtual SqlColumns getColumns() const override;

    void setTrainingStandardID( const ID &trainingStandardID );
    Q_ALWAYS_INLINE ID trainingStandardID() const { return m_trainingStandardID; }

    Q_INVOKABLE bool addShot( int number, double radius, double alpha, double arrowDiameter );

private:
    ID m_trainingStandardID;
};

#endif // SHOTMODEL_H
