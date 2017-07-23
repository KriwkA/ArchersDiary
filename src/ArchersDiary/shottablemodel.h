#ifndef SHOTTABLEMODEL_H
#define SHOTTABLEMODEL_H

#include <QAbstractTableModel>

class ExcerciseModel;
class StandardExcerciseModel;
class SimpleShotModel;

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

    Q_INVOKABLE bool setShotScore(int row, int col, int score);
    Q_INVOKABLE QVariant shotScore(int row, int col) const;

    virtual QHash<int, QByteArray> roleNames() const override;

    int round() const;

public slots:
    void setRound(int round);

private slots:
    void onShotsModelDataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles );

private:
    static ExcerciseModel* excercises();
    static StandardExcerciseModel* standardExcercises();
    static SimpleShotModel* shotModel();
    int shotNumber(int row, int col) const;
    static int shotNumber(int row, int col, int colCount);
    void notifyScoreChanging(int shotNumber );

    int calcSummForShot( int row ) const;

signals:
    void roundChanged(int round);

};





#endif // SHOTTABLEMODEL_H
