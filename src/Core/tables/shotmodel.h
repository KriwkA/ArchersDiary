#ifndef SHOTMODEL_H
#define SHOTMODEL_H

#include "baseshotmodel.h"

class CORESHARED_EXPORT ShotModel : public BaseShotModel
{
    Q_OBJECT
public:
    explicit ShotModel( QSqlDatabase* db, QObject* parent = nullptr );
    virtual SqlColumns getColumns() const override;
    Q_INVOKABLE bool addShot(int number, double radius, double alpha, double arrowDiameter );
};

#endif // SHOTMODEL_H
