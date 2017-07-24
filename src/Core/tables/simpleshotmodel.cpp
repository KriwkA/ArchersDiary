#include "precomp.h"
#include "simpleshotmodel.h"
#include "diarytables.h"
#include "trainingstandardmodel.h"

SimpleShotModel::SimpleShotModel(QSqlDatabase *db, QObject *parent)
    : BaseShotModel( db, parent )
{
    setTable( "SimpleShotModel" );
}


SqlTableModel::SqlColumns SimpleShotModel::getColumns() const
{
    auto trainingStandardModel = DiaryTables::getTableModel( TableType::TrainingStandards );
    if( trainingStandardModel != nullptr )
    {
        SqlTableModel::SqlColumn id = SqlColumn::createPrimaryKey();

        SqlColumn trainingStandard = SqlColumn::createForeign( trainingStandardModel );
        SqlColumn number( "Number", ftINTEGER );
        SqlColumn round( "Round", ftINTEGER );
        SqlColumn score( "Score", ftINTEGER );

        return { id, trainingStandard, number, round, score };
    }
    return SqlColumns();
}

bool SimpleShotModel::setShot(int number, int score)
{
    if( trainingStandardID() != FAKE_ID )
    {
        if( shotExists( number ) )
            return updateShot( number, score );
        return addShot( number, score );
    }
    return false;
}

int SimpleShotModel::shot(int number) const
{
    if( trainingStandardID() != FAKE_ID )
    {
        QSqlRecord rec = recByShotNumber( number );
        if( rec.contains( "Score" ) )
            return rec.value( "Score" ).toInt();
    }
    return -1;
}

bool SimpleShotModel::addShot(int number, int score)
{    
    return insertValues( { trainingStandardID(), number, round(), score } );
}

bool SimpleShotModel::shotExists(int number)
{
    return !recByShotNumber( number ).isEmpty();
}

bool SimpleShotModel::updateShot(int number, int score)
{
    int row;
    QSqlRecord shotRec = recByShotNumber( number, &row );

    if( !shotRec.isEmpty() )    
        return setData( row, score, roleFromRoleName( "Score" ) );

    return false;
}

QSqlRecord SimpleShotModel::recByShotNumber(int number, int *row) const
{
    QSqlRecord rec;
    for(int i = 0; i < rowCount(); ++i) {
        rec = record( i );
        if( rec.field("Number").value().toInt() == number && rec.field("Round").value().toInt() == round() ) {
            if( row != nullptr )
                *row = i;
            return rec;
        }
    }
    if( row != nullptr )
        *row = -1;
    return QSqlRecord();
}
