#ifndef STANDARDEXCERSICEMODEL_H
#define STANDARDEXCERSICEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT StandardExcerciseModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID standardID READ standardID WRITE setStandardID)
public:
    explicit StandardExcerciseModel( QSqlDatabase* db, QObject* parent = nullptr );
    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID standardID() const { return m_standardID; }
    void setStandardID(ID standardID);

    Q_INVOKABLE bool addExcercise( ID excerciseID );

private:
    ID m_standardID;
};

#endif // STANDARDEXCERSICEMODEL_H
