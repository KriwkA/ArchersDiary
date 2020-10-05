#ifndef TRAININGCALENDAR_H
#define TRAININGCALENDAR_H

#include <QQuickPaintedItem>
#include <QDate>

class QVariantAnimation;

struct DayPaintedData
{
    QRect rect;
    QRect numberRect;
    QColor backgroundColor;
    QColor numberColor;
    QDate date;
    bool hasTraining = false;
};

class TrainingCalendar : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Q_PROPERTY(int cellIndent READ cellIndent WRITE setCellIndent)
    Q_PROPERTY(int monthHeaderHeight READ monthHeaderHeight WRITE setMonthHeaderHeight)
    Q_PROPERTY(int weakHeaderHeight READ weakHeaderHeight WRITE setWeakHeaderHeight)  

    Q_PROPERTY(int currYear READ currYear WRITE setCurrYear)
    Q_PROPERTY(int currMonth READ currMonth WRITE setCurrMonth)
    Q_PROPERTY(QDate selectedDay READ selectedDay NOTIFY daySelected)

    explicit TrainingCalendar( QQuickItem* parent = nullptr );

    void paint(QPainter *painter) Q_DECL_OVERRIDE;

    int cellIndent() const;
    int monthHeaderHeight() const;
    int weakHeaderHeight() const;

    const QPoint& dayNumberTextIndent() const;

    int currYear() const;
    int currMonth() const;
    QDate selectedDay() const;

signals:
    void currMonthChanged(QDate);
    void daySelected(QDate);


public slots:
    void setCellIndent(int cellIndent);
    void setMonthHeaderHeight(int monthHeaderHeight);
    void setWeakHeaderHeight(int weakHeaderHeight);

    void setCurrYear(int currYear);
    void setCurrMonth(int currMonth);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void setDrawXDif( const QVariant& value );
    void setDrawXDif( int value );
    void finishScrollAnimation();
    void finishCancelScrollAnimation();

private:
    void setSelectedDay( const QDate& day );
    void setCurrMonth(const QDate &currMonth);
    static QDate nextMonth( const QDate& from, bool next );
    void scrollMonth(bool right, bool cancel_scroll = false );

    int scrollNextIndent() const;

    void drawMonthHeader( QPainter* painter );
    void drawMonthHeader(QPainter *painter, const QDate& currMonth, int dx);

    void drawWeakHeader( QPainter* painter );
    void drawWeakHeader( QPainter* painter, int dx );

    void drawDayCells( QPainter* painter );
    void drawDayCells(QPainter* painter, const QVector<DayPaintedData>& cell_rects, int dx);

    QRect monthHeaderRect() const;
    QRect weakHeaderRect() const;
    QRect daysViewPortRect() const;
    QVector<DayPaintedData> calcCellRects( const QDate& currMonth ) const;

    int FirstMondayIndexInCellRects() const;

    QPair<int, int> sizeAndRest( bool width, int parts ) const;

    QVector<DayPaintedData> m_cellRects;
    QVector<DayPaintedData> m_scrollCellRects;

    int m_cellIndent = 1;
    int m_monthHeaderHeight = 34;
    int m_weakHeaderHeight = 28;
    QDate m_currMonth{ QDate::currentDate().year(), QDate::currentDate().month(), 1 };
    QDate m_selectedDay{ QDate::currentDate() };
    QFont m_weakHeaderFont;

    bool m_scrollOn = false;
    QPoint m_lastMovePoint = QPoint( -1, -1 );
    int m_drawXDif = 0;        

    QVariantAnimation* m_scrollAnimation = nullptr;    
};







#endif // TRAININGCALENDAR_H
