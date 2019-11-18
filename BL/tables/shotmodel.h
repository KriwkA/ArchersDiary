#ifndef SHOTMODEL_H
#define SHOTMODEL_H

#include <bl_global.h>

#include "baseshotmodel.h"

class BL_SHARED_EXPORT ShotModel : public BaseShotModel
{
    Q_OBJECT
public:
    explicit ShotModel( QSqlDatabase& db, QObject* parent = nullptr );
    const core::db::SqlColumnList& getColumns() const noexcept override;

    Q_INVOKABLE bool addShot(int number, double radius, double alpha, double arrowDiameter );

};

#endif // SHOTMODEL_H
