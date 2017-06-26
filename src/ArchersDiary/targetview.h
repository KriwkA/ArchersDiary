#ifndef TARGETVIEW_H
#define TARGETVIEW_H

#include <QQuickPaintedItem>

class ShotModel;

class Shot
{
    Q_PROPERTY(double length READ length WRITE setLength)
    Q_PROPERTY(double alpha READ alpha WRITE setAlpha)
public:
    double length() const;
    void setLength(double length);
    double aplha() const;
    void setAplha(double aplha);
private:
    double m_length;
    double m_aplha;
};

class TargetView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(ShowType showType READ showType WRITE setShowType)

public:
    enum ShowType
    {
        JustTarget,
        NewShot,
        ShotModel,
    };
    Q_DECLARE_METATYPE( ShowType )

    explicit TargetView( QQuickItem* parent = nullptr );

    ShowType showType() const;
    void setShowType(ShowType showType);

public slots:

private:
    ShowType m_showType;

};

#endif // TARGETVIEW_H
