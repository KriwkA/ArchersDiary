#ifndef TRAININGTABLEMODEL_H
#define TRAININGTABLEMODEL_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT TrainingTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID archerID READ archerID WRITE setArcherID NOTIFY archerIDChanged)
    Q_PROPERTY(int shotCount READ shotCount WRITE setShotCount NOTIFY shotCountChanged)
    Q_PROPERTY(ID currentTrainingID READ currentTrainingID WRITE setCurrentTrainingID NOTIFY currentTrainingIDChanged)
public:
    explicit TrainingTableModel(QSqlDatabase* db, QObject* parent = nullptr);

    virtual SqlColumns getColumns() const override;
    virtual bool select() override;

    Q_ALWAYS_INLINE ID archerID() const { return m_archerID; }
    int shotCount() const;
    Q_ALWAYS_INLINE ID currentTrainingID() const { return m_currentTrainingID; }

    Q_INVOKABLE bool addTraining();


public slots:
    void setArcherID(ID archerID);
    void setShotCount(int shotCount);
    void setCurrentTrainingID(ID currentTrainingID)
    {
        if (m_currentTrainingID == currentTrainingID)
            return;

        m_currentTrainingID = currentTrainingID;
        emit currentTrainingIDChanged(m_currentTrainingID);
    }

signals:
    void archerIDChanged( ID id );
    void shotCountChanged( int count );
    void currentTrainingIDChanged(ID currentTrainingID);

private:
    ID m_archerID;
    ID m_currentTrainingID;

    QModelIndex currentTrainingModelIndex() const;

};

#endif // TRAININGTABLEMODEL_H
