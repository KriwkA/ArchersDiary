#ifndef SIMPLESHOTMODEL_H
#define SIMPLESHOTMODEL_H

#include "baseshotmodel.h"

class CORESHARED_EXPORT SimpleShotModel : public BaseShotModel
{
    Q_OBJECT
public:
    explicit SimpleShotModel(QSqlDatabase *db, QObject *parent = nullptr);
    virtual SqlColumns getColumns() const override;

    Q_INVOKABLE bool setShot( int number, int score );
    Q_INVOKABLE int shot( int number ) const;

private:
    bool addShot(int number, int score );
    bool shotExists(int number);
    bool updateShot(int number, int score);
    QSqlRecord recByShotNumber( int number, int* row = nullptr ) const;
};

#endif // SIMPLESHOTMODEL_H
