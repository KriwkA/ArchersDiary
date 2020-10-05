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

    explicit TrainingCalendar( QQuickItem* parent = nullptr );

    void paint(QPainter *painter) Q_DECL_OVERRIDE;

    int cellIndent() const;
    int monthHeaderHeight() const;
    int weakHeaderHeight() const;

    const QPoint& dayNumberTextIndent() const;

    int currYear() const;
    int currMonth() const;

signals:
    void currMonthChanged(QDate);


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
    QVector<DayPaintedData> calcCellRects( const QDate& currMonth );

    int FirstMondayIndexInCellRects() const;

    QPair<int, int> sizeAndRest( bool width, int parts ) const;

    QVector<DayPaintedData> m_cellRects;
    QVector<DayPaintedData> m_scrollCellRects;

    int m_cellIndent = 1;
    int m_monthHeaderHeight = 34;
    int m_weakHeaderHeight = 28;
    QDate m_currMonth;
    QFont m_weakHeaderFont;
    QFont m_dayNumberFont;
    QFont m_monthHeaderFont;

    QColor m_backgroundColor = QColor( "#F0F0F0" );
    QColor m_dayColor = QColor( "#CCCCCC" );
    QColor m_dayNumberTextColor = QColor("#000000");
    QColor m_currDayNumberTextColor = QColor( "#FFFFFF" );
    QColor m_currDayColor = QColor( "#0000FF" );
    Qt::AlignmentFlag m_dayTextAlign = static_cast<Qt::AlignmentFlag>( static_cast<int>(Qt::AlignRight) | static_cast<int>(Qt::AlignTop) );

    QColor m_weakHeaderTextColor;
    QColor m_monthHeaderTextColor;

    bool m_scrollOn = false;
    QPoint m_lastMovePoint = QPoint( -1, -1 );
    int m_drawXDif = 0;        

    QVariantAnimation* m_scrollAnimation = nullptr;


    QPoint m_dayNumberTextIndent;
};







#endif // TRAININGCALENDAR_H
