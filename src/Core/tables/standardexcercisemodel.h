#ifndef STANDARDEXCERSICEMODEL_H
#define STANDARDEXCERSICEMODEL_H

#include <database/sqltablemodel.h>

class StandardModel;
class ExcerciseModel;

class CORESHARED_EXPORT StandardExcerciseModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID standardID READ standardID WRITE setStandardID NOTIFY standardIDChanged)
public:
    explicit StandardExcerciseModel( QSqlDatabase* db, QObject* parent = nullptr );
    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID standardID() const { return m_standardID; }
    void setStandardID(ID standardID);

    Q_INVOKABLE bool addExcercise( ID standardID, ID excerciseID, int count = 1 );
    virtual bool createTable(QString &error) override;

    Q_INVOKABLE int excerciseCount() const;
    Q_INVOKABLE int excerciseId( int excersiceNumber ) const;

signals:
    void standardIDChanged( ID id );

private:
    bool addExcercise(const QString& standardName, const QString &excerciseName, int count = 1);
    StandardModel* standards() const;
    ExcerciseModel* excercises() const;

    ID m_standardID;
};

#endif // STANDARDEXCERSICEMODEL_H
