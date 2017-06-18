#ifndef TARGETMODEL_H
#define TARGETMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT TargetModel : public SqlTableModel
{
    Q_OBJECT
public:
    explicit TargetModel( QSqlDatabase* db, QObject* parent);
    virtual SqlColumns getColumns() const override;

    Q_INVOKABLE bool addTarget(int circleCount, int growingRadius, const QList<int>& circleColors );
};

#endif // TARGETMODEL_H
