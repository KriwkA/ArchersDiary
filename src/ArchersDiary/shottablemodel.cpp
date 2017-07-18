#include "shottablemodel.h"
#include "diarytables.h"
#include "tables/excercisemodel.h"
#include "tables/standardexcercisemodel.h"
#include "tables/shotmodel.h"

ShotTableModel::ShotTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    memset(m_series, -1, sizeof( m_series ));
}

int ShotTableModel::rowCount(const QModelIndex &parent) const
{
    if( !parent.isValid() )
        return excercises()->seriesCount( standardExcercises()->excerciseId( m_round ) );
    return 0;
}

int ShotTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )
    return excercises()->shotPerSerie( standardExcercises()->excerciseId( m_round ) );
}

QVariant ShotTableModel::data(const QModelIndex &index, int role) const
{
    if( Qt::UserRole <= role && role <= SeriesResult && index.isValid() )
    {
        return shotScore(index.row(), role - Qt::UserRole );
    }
    return QVariant();
}

bool ShotTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if( index.isValid() && Qt::UserRole <= role && role < SeriesResult && value.type() == QVariant::Int )
    {
        bool goodCast;
        int row = index.row();
        int col = role - Qt::UserRole;
        int score = value.toInt( &goodCast );

        if( goodCast ) {
            m_series[ row ][ col ] = score;
            notifyScoreChenging( row, col );
            return true;
        }
    }

    return false;
}

QVariant ShotTableModel::shotScore(int row, int col) const
{
    if( col == 6 )
        return calcSummForShot( row );
    int score = m_series[ row ][ col ];
    if(score != -1)
        return score != 0 ? QVariant( score ) : QVariant( "M" );
    return "";
}


QHash<int, QByteArray> ShotTableModel::roleNames() const
{
    static const QHash<int, QByteArray> roleNames = {
        { FirstArrow, "FirstArrow" },
        { SecondArrow, "SecondArrow" },
        { ThirdArrow, "ThirdArrow" },
        { FourthArrow, "FourthArrow" },
        { FifthArrow, "FifthArrow" },
        { SixthArrow, "SixthArrow" },
        { SeriesResult, "SeriesResult" }
    };
    return roleNames;
}

ExcerciseModel *ShotTableModel::excercises()
{
    return static_cast< ExcerciseModel* >( DiaryTables::getTableModel( TableType::Excercises ) );
}

StandardExcerciseModel *ShotTableModel::standardExcercises()
{
    return static_cast< StandardExcerciseModel* >( DiaryTables::getTableModel( TableType::StandardExcersices ) );
}

ShotModel *ShotTableModel::shots()
{
    return static_cast< ShotModel* >( DiaryTables::getTableModel( TableType::Shots ) );
}

void ShotTableModel::notifyScoreChenging(int row, int shotNumber)
{
    QModelIndex rowIndex = index( row, 0 );
    emit dataChanged( rowIndex, rowIndex, QVector<int>() << shotNumber + Qt::UserRole );

    int nRow = rowCount();
    for( int i = row; i < nRow; ++i ) {
        rowIndex = index( i, 0 );
        emit dataChanged( rowIndex, rowIndex, QVector<int>() << SeriesResult );
    }
}


int ShotTableModel::calcSummForShot(int row) const
{
    // FIXME: optimize me
    int summ = 0;
    int val;
    int colCount = columnCount();
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < colCount; ++j ) {
            val = m_series[i][j];
            if( val != -1 )
                summ += val;
        }
    }
    return summ;
}
