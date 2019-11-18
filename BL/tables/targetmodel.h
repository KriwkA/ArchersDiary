#ifndef TARGETMODEL_H
#define TARGETMODEL_H

#include <bl_global.h>

#include <db/sqltablemodel.h>

struct BL_SHARED_EXPORT Target
{
    int circleCount;
    QString name;
    QList<int> scores;
    QList<double> radiuses;
    QList<int> colors;

    static QString getFitaTargetName( double tenSize, int circleCount );
    static Target getFitaTarget( double tenSize, int circleCount );
    static int getFitaColor( int score );
};

class BL_SHARED_EXPORT TargetModel : public core::db::SqlTableModel
{
    Q_OBJECT
public:
    explicit TargetModel( QSqlDatabase& db, QObject* parent = nullptr);
    const core::db::SqlColumnList& getColumns() const noexcept override;
    virtual bool createTable( QString& error ) override;

    Q_INVOKABLE bool addTarget( const Target& target );
    int fitaTargetId( const QString& name );
};



#endif // TARGETMODEL_H
