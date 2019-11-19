#pragma once

#include <bl_global.h>
#include <db/sqltablemodel.h>

#include <QDate>

class BL_SHARED_EXPORT TrainingTableModel : public core::db::SqlTableModel
{
    Q_OBJECT
public:
    Q_PROPERTY(core::db::ID archerID READ archerID WRITE setArcherID NOTIFY archerIDChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)

    explicit TrainingTableModel(QSqlDatabase& db, QObject* parent = nullptr);

    const core::db::SqlColumnList& getColumns() const noexcept override;

    Q_ALWAYS_INLINE core::db::ID archerID() const { return m_archerID; }
    Q_ALWAYS_INLINE QDate date() const { return m_date; }
    int shotCount() const;

    Q_INVOKABLE bool addTraining(core::db::ID standardID);


public slots:
    void setArcherID(core::db::ID archerID);
    void setDate(const QDate& date);

signals:
    void archerIDChanged(core::db::ID id);
    void dateChanged(const QDate& date);

private:
    void updateFilter();

    core::db::ID m_archerID;
    QDate m_date = QDate::currentDate();

};
