#ifndef BASESHOTMODEL_H
#define BASESHOTMODEL_H

#include <database/sqltablemodel.h>


class CORESHARED_EXPORT BaseShotModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID trainingStandardID READ trainingStandardID WRITE setTrainingStandardID NOTIFY trainingStandardIDChanged)
    Q_PROPERTY(int round READ round WRITE setRound NOTIFY roundChanged)
public:
    explicit BaseShotModel( QSqlDatabase* db, QObject* parent = nullptr );

    Q_ALWAYS_INLINE ID trainingStandardID() const { return m_trainingStandardID; }
    Q_ALWAYS_INLINE int round() const { return m_round; }

public slots:
    void setTrainingStandardID( const ID &trainingStandardID );
    void setRound(int round);    

signals:
    void trainingStandardIDChanged( ID id );
    void roundChanged(int round);

protected:
    virtual void resetFilter();
    void updateFilter();

private:
    ID m_trainingStandardID;
    int m_round;
};

#endif // BASESHOTMODEL_H
