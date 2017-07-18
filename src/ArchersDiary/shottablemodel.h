#ifndef SHOTTABLEMODEL_H
#define SHOTTABLEMODEL_H

#include <QAbstractTableModel>

class ExcerciseModel;
class StandardExcerciseModel;
class ShotModel;

class ShotTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int round READ round WRITE setRound NOTIFY roundChanged)
public:        
    explicit ShotTableModel(QObject *parent = nullptr);

    enum Roles {
        FirstArrow = Qt::UserRole,
        SecondArrow,
        ThirdArrow,
        FourthArrow,
        FifthArrow,
        SixthArrow,
        SeriesResult,
    };

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Q_INVOKABLE QVariant shotScore(int row, int col) const;

    virtual QHash<int, QByteArray> roleNames() const override;

    Q_ALWAYS_INLINE int round() const { return m_round; }

public slots:
    Q_ALWAYS_INLINE void setRound(int round)
    {
        if (m_round == round)
            return;

        m_round = round;
        emit roundChanged(m_round);
    }

signals:
    void roundChanged(int round);

private:
    static ExcerciseModel* excercises();
    static StandardExcerciseModel* standardExcercises();
    static ShotModel* shots();
    void notifyScoreChenging( int row, int shotNumber );

    int calcSummForShot( int row ) const;

    int m_series[10][6];

    int m_round = 0;

};

#endif // SHOTTABLEMODEL_H
