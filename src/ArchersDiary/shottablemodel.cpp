#include "shottablemodel.h"
#include "diarytables.h"
#include "tables/excercisemodel.h"
#include "tables/standardexcercisemodel.h"
#include "tables/simpleshotmodel.h"
#include <QSqlRecord>

ShotTableModel::ShotTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    auto shots = shotModel();
    if( shots != nullptr ) {
        connect( shots, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                 this, SLOT(onShotsModelDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        connect( shots, SIGNAL(modelAboutToBeReset()),
                 this, SIGNAL(modelAboutToBeReset()));
        connect( shots, SIGNAL(modelReset()),
                 this, SIGNAL(modelReset()));
    }
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
    if( index.isValid() )
    {
        switch (role) {
        case FirstArrow:
        case SecondArrow:
        case ThirdArrow:
        case FourthArrow:
        case FifthArrow:
        case SixthArrow:
            return shotScore(index.row(), role - Qt::UserRole );
        case SerieResult:
            return serieScore( index.row() );
        }

    }
    return QVariant();
}

bool ShotTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if( index.isValid() && FirstArrow <= role && role <= SixthArrow && value.type() == QVariant::Int )
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
    if( shotModel()->setShot( shotNumber( row, col ), score ) )
    {
        auto idx = index( row, columnCount() - 1 );
        emit dataChanged( idx, idx );
        return true;
    }
    return false;
}


QVariant ShotTableModel::shotScore(int row, int col) const
{
    auto shots = shotModel();
    if( shots != nullptr ) {        
        int score = shots->shot( shotNumber( row, col ) );
        if(score != -1)
            return score != 0 ? QVariant( score ) : QVariant( "M" );
    }
    return "";
}

int ShotTableModel::serieScore(int serie) const
{
    int total = 0;
    auto shots = shotModel();
    if( shots != nullptr && serie < rowCount() ) {
        int cols = columnCount() - 1;
        int shot;
        for(int j = 0; j < cols; ++j) {
            shot = shots->shot( shotNumber( serie, j, cols ) );
            if( shot != -1 )
                total += shot;
        }
    }

    return total;
}

int ShotTableModel::totalScore() const
{
    int serieCount = rowCount();
    int result = 0;
    for(int i = 0; i < serieCount; ++i)
        result += serieScore(i);
    return result;
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
        { SerieResult, "SerieResult" }
    };
    return roleNames;
}

void ShotTableModel::notifyScoreChanging(int shotNumber)
{
    int colCount = columnCount();
    int row = shotNumber / colCount;
    int col = shotNumber % colCount;
    QModelIndex shotIndex = index( row, col );    
    QModelIndex serieScoreIndex = index( row, colCount - 1 );
    emit dataChanged( shotIndex, shotIndex );
    emit dataChanged( serieScoreIndex, serieScoreIndex );
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
    Q_UNUSED(roles);
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

Q_ALWAYS_INLINE int ShotTableModel::shotNumber( int row, int col ) const
{
    return shotNumber( row, col, columnCount() - 1 );
}

Q_ALWAYS_INLINE int ShotTableModel::shotNumber(int row, int col, int colCount)
{
    return row * colCount + col;
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
