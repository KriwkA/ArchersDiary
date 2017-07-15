#ifndef TRAININGTABLEMODEL_H
#define TRAININGTABLEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT TrainingTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID archerID READ archerID WRITE setArcherID NOTIFY archerIDChanged)
    Q_PROPERTY(int shotCount READ shotCount WRITE setShotCount NOTIFY shotCountChanged)
public:
    explicit TrainingTableModel(QSqlDatabase* db, QObject* parent = nullptr);

    virtual SqlColumns getColumns() const override;
    virtual bool select() override;

    Q_ALWAYS_INLINE ID archerID() const { return m_archerID; }
    void setArcherID(ID archerID);

    int shotCount() const;
    void setShotCount(int shotCount);

    Q_INVOKABLE bool addTraining();


signals:
    void archerIDChanged( ID id );
    void shotCountChanged( int count );

private:
    ID m_archerID;

    QModelIndex indexFromArcherID( ID archerID ) const;
};

#endif // TRAININGTABLEMODEL_H
