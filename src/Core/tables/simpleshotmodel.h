#ifndef SIMPLESHOTMODEL_H
#define SIMPLESHOTMODEL_H

#include "baseshotmodel.h"

class CORESHARED_EXPORT SimpleShotModel : public BaseShotModel
{
    Q_OBJECT
public:
    explicit SimpleShotModel(QSqlDatabase *db, QObject *parent = nullptr);
    virtual SqlColumns getColumns() const override;
    Q_INVOKABLE bool addShot(int number, int score );
};

#endif // SIMPLESHOTMODEL_H
