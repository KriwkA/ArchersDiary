#include <precomp.h>
#include "trainingtablemodel.h"
#include "diarytables.h"
#include <QDateTime>

TrainingTableModel::TrainingTableModel(QSqlDatabase *db, QObject *parent)
    : SqlTableModel(db, parent)
    , m_archerID( FAKE_ID )
    , m_currentTrainingID( FAKE_ID )
{
    setTable("Training");
}

SqlTableModel::SqlColumns TrainingTableModel::getColumns() const
{    
    auto archerModel = DiaryTables::getTableModel( TableType::Archrers );
    if( archerModel != nullptr )
    {
        SqlTableModel::SqlColumn id = SqlColumn::createPrimaryKey();
        SqlTableModel::SqlColumn archer = SqlColumn::createForeign( archerModel );

        SqlTableModel::SqlColumn date;
        date.name = "Date";
        date.dataType = ftINTEGER;

        SqlTableModel::SqlColumn simpleShots;
        simpleShots.name = "SimpleShots";
        simpleShots.dataType = ftINTEGER;

        return { id, archer, date, simpleShots };
    }    
    return SqlColumns();
}

bool TrainingTableModel::select()
{
    if( SqlTableModel::select() ) {
        if( m_archerID != FAKE_ID ) {
            emit shotCountChanged( shotCount() );
        }
        return true;
    }
    return false;
}

void TrainingTableModel::setArcherID(ID archerID)
{
    if( m_archerID != archerID )
    {
        m_archerID = archerID;
        if(m_archerID != FAKE_ID )
            setFilter(QString("Archer=%0").arg(m_archerID));
        else
            resetFilter();
        emit archerIDChanged( m_archerID );
    }
}

int TrainingTableModel::shotCount() const
{
    auto modelIndex = currentTrainingModelIndex();
    if( modelIndex.isValid() ) {
        return data( modelIndex, roleFromRoleName( "SimpleShots" ) ).toInt();
    }
    return 0;
}

void TrainingTableModel::setShotCount(int shotCount)
{
    if( shotCount != this->shotCount() ) {
        auto modelIndex = currentTrainingModelIndex();
        if( modelIndex.isValid() && setData( modelIndex.row(), shotCount, roleFromRoleName( "SimpleShots" ) ) )
            emit shotCountChanged( shotCount );        
    }
}

QModelIndex TrainingTableModel::currentTrainingModelIndex() const
{
    if( m_currentTrainingID != FAKE_ID )
    {
        int rows = rowCount();
        QModelIndex modelIndex;
        bool ok = false;
        for( int i = 0; i < rows; ++i ) {
            modelIndex = std::move( index(i, 0) );
            if( data( modelIndex, roleFromRoleName( "Id" ) ).toInt( &ok ) == m_currentTrainingID && ok )
                return std::move( modelIndex );
        }
    }

    return QModelIndex();
}

bool TrainingTableModel::addTraining()
{
    if(m_archerID >= 0)
        return insertValues({ m_archerID, QDateTime::currentDateTime().toSecsSinceEpoch(), 0 });
    qWarning() << "Invalid archer Id";
    return false;
}

