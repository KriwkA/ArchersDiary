#ifndef TARGETMODEL_H
#define TARGETMODEL_H

#include <database/sqltablemodel.h>

struct CORESHARED_EXPORT Target
{
    int circleCount;
    QString name;
    QList<int> scores;
    QList<double> radiuses;
    QList<int> colors;

    static Target getFitaTarget( double tenSize, int circleCount );
    static int getFitaColor( int score );
};

class CORESHARED_EXPORT TargetModel : public SqlTableModel
{
    Q_OBJECT
public:
    explicit TargetModel( QSqlDatabase* db, QObject* parent);
    virtual SqlColumns getColumns() const override;
    virtual bool init( QString& error ) override;

    Q_INVOKABLE bool addTarget( const Target& target );
};



#endif // TARGETMODEL_H
