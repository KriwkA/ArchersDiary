#ifndef ARROWSTABLE_H
#define ARROWSTABLE_H

#include <database/sqltablemodel.h>

class CORESHARED_EXPORT ArrowsTableModel : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(ID archerID READ archerID WRITE setArcherID NOTIFY archerIDChanged)
public:
    explicit ArrowsTableModel(QSqlDatabase* db, QObject* parent = nullptr);
    virtual SqlColumns getColumns() const override;

    Q_ALWAYS_INLINE ID archerID() const { return m_archerID; }
    void setArcherID( ID archerID );

    Q_INVOKABLE bool addArrow( const QString& name, double spine, double length, double diameter );

signals:
    void archerIDChanged( ID id );

private:
    ID m_archerID;
};

#endif // ARROWSTABLE_H
