#include "shottablemodel.h"
#include "diarytables.h"
#include "tables/excercisemodel.h"
#include "tables/standardexcercisemodel.h"
#include "tables/simpleshotmodel.h"
#include <QSqlRecord>

ShotTableModel::ShotTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    if( shotModel() != nullptr )
        connect( shotModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                 this, SLOT(onShotsModelDataChanged(QModelIndex,QModelIndex,QVector<int>)));
}

int ShotTableModel::rowCount(const QModelIndex &parent) const
{
    if( !parent.isValid() )
        return excercises()->seriesCount( standardExcercises()->excerciseId( round() ) );
    return 0;
}

int ShotTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )
    return excercises()->shotPerSerie( standardExcercises()->excerciseId( round() ) ) + 1;
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
        int score = value.toInt( &goodCast );
        if( goodCast )
            return setShotScore( index.row(), role - Qt::UserRole, score );
    }

    return false;
}

bool ShotTableModel::setShotScore(int row, int col, int score)
{
    int colCount = columnCount();
    int shotNumber = colCount * row + col;
    shotModel()->setShot( shotNumber, score );
    return true;
}


QVariant ShotTableModel::shotScore(int row, int col) const
{
    auto shots = shotModel();
    if( shots != nullptr ) {
        if( col == 6 )
            return calcSummForShot( row );
        int score = shots->shot( shotNumber( row, col ) );
        if(score != -1)
            return score != 0 ? QVariant( score ) : QVariant( "M" );
    }
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

Q_ALWAYS_INLINE int ShotTableModel::shotNumber( int row, int col ) const
{
    return shotNumber( row, col, columnCount() );
}

Q_ALWAYS_INLINE int ShotTableModel::shotNumber(int row, int col, int colCount)
{
    return row * colCount + col;
}

void ShotTableModel::notifyScoreChanging(int shotNumber)
{
    emit dataChanged( index(0, 0), index( rowCount(), columnCount()), {
                          FirstArrow ,
                          SecondArrow,
                          ThirdArrow,
                          FourthArrow,
                          FifthArrow,
                          SixthArrow,
                          SeriesResult
                      } );
    return;

    int colCount = columnCount();
    int row = shotNumber / colCount;
    int col = shotNumber % colCount;
    QModelIndex shotIndex = index( row, col );
    QModelIndex totalIndex = index( row, 6 );
    emit dataChanged( shotIndex, shotIndex, { Qt::DisplayRole, col + Qt::UserRole } );
    emit dataChanged( totalIndex, totalIndex, { Qt::DisplayRole, SeriesResult } );

}

int ShotTableModel::calcSummForShot(int row) const
{
    int summ = 0;
    auto shots = shotModel();
    if( shots != nullptr ) {

        int val;
        int colCount = columnCount();
        for(int i = 0; i < colCount; ++i ) {
            val = shots->shot( shotNumber( row, i, colCount ) );
            if( val != -1 )
                summ += val;
        }
    }
    return summ;
}
int ShotTableModel::round() const
{
    return shotModel() != nullptr ? shotModel()->round() : 0;
}

void ShotTableModel::setRound(int round)
{
    auto shots = shotModel();
    if (shots == nullptr || shots->round() == round)
        return;

    shots->setRound( round );
    emit roundChanged( shots->round() );
}

void ShotTableModel::onShotsModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    if( topLeft.column() == 4 )
    {
        for( int i = topLeft.row(); i <= bottomRight.row(); ++i )
        {
            auto rec = shotModel()->record( i );
            if( rec.contains("Number") )
                notifyScoreChanging( rec.value("Number").toInt() );
        }
    }
}

ExcerciseModel *ShotTableModel::excercises()
{
    return static_cast< ExcerciseModel* >( DiaryTables::getTableModel( TableType::Excercises ) );
}

StandardExcerciseModel *ShotTableModel::standardExcercises()
{
    return static_cast< StandardExcerciseModel* >( DiaryTables::getTableModel( TableType::StandardExcersices ) );
}

SimpleShotModel *ShotTableModel::shotModel()
{
    return static_cast< SimpleShotModel* >( DiaryTables::getTableModel( TableType::SimpleShots ) );
}
