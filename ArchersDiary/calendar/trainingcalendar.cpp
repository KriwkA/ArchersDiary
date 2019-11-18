#include "trainingcalendar.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QVariantAnimation>

#include <array>

static constexpr int SHOW_WEAK_COUNT = 6;
static constexpr int DAY_PER_WEAK = 7;

TrainingCalendar::TrainingCalendar(QQuickItem *parent)
    : QQuickPaintedItem( parent )
    , m_currMonth( QDate::currentDate().year(), QDate::currentDate().month(), 1 )
{    
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(ItemAcceptsInputMethod, true);
}

void TrainingCalendar::paint(QPainter *painter)
{
    if( painter == nullptr )
        return;

    painter->setPen( Qt::NoPen );
    painter->setBrush( backgroundColor() );
    painter->drawRect( 0, 0, width(), height() );

    drawMonthHeader( painter );
    drawWeakHeader( painter );
    drawDayCells( painter );
}

int TrainingCalendar::cellIndent() const
{
    return m_cellIndent;
}

int TrainingCalendar::monthHeaderHeight() const
{
    return m_monthHeaderHeight;
}

int TrainingCalendar::weakHeaderHeight() const
{
    return m_weakHeaderHeight;
}

const QColor &TrainingCalendar::dayColor() const
{
    return m_dayColor;
}

const QFont &TrainingCalendar::weakHeaderFont() const
{
    return m_weakHeaderFont;
}

const QFont &TrainingCalendar::dayNumberFont() const
{
    return m_dayNumberFont;
}

const QColor &TrainingCalendar::weakHeaderTextColor() const
{
    return m_weakHeaderTextColor;
}

const QColor &TrainingCalendar::dayNumberTextColor() const
{
    return m_dayNumberTextColor;
}

const QColor &TrainingCalendar::currDayNumberTextColor() const
{
    return m_currDayNumberTextColor;
}

const QFont &TrainingCalendar::monthHeaderFont() const
{
    return m_monthHeaderFont;
}

const QColor &TrainingCalendar::monthHeaderTextColor() const
{
    return m_monthHeaderTextColor;
}

int TrainingCalendar::currYear() const
{
    return m_currMonth.year();
}

int TrainingCalendar::currMonth() const
{
    return m_currMonth.month();
}

const QColor &TrainingCalendar::backgroundColor() const
{
    return m_backgroundColor;
}

const QPoint &TrainingCalendar::dayNumberTextIndent() const
{
    return m_dayNumberTextIndent;
}

int TrainingCalendar::dayTextAlign() const
{
    return m_dayTextAlign;
}

const QColor &TrainingCalendar::currDayColor() const
{
    return m_currDayColor;
}

void TrainingCalendar::setCellIndent(int cellIndent)
{
    if (m_cellIndent == cellIndent)
        return;

    m_cellIndent = cellIndent;
    update(daysViewPortRect());
}

void TrainingCalendar::setMonthHeaderHeight(int monthHeaderHeight)
{
    m_monthHeaderHeight = monthHeaderHeight;
    update( monthHeaderRect() );
}

void TrainingCalendar::setWeakHeaderHeight(int weakHeaderHeight)
{
    m_weakHeaderHeight = weakHeaderHeight;
    update( weakHeaderRect() );
}

void TrainingCalendar::setDayColor(const QColor &cellColor)
{
    m_dayColor = cellColor;
    update( daysViewPortRect() );
}

void TrainingCalendar::setWeakFont(const QFont &weakHeaderFont)
{
    m_weakHeaderFont = weakHeaderFont;
    update( weakHeaderRect() );
}

void TrainingCalendar::setDayNumberFont(const QFont &dayNumberFont)
{
    m_dayNumberFont = dayNumberFont;
    update( daysViewPortRect() );
}

void TrainingCalendar::setWeakHeaderTextColor(const QColor &weakHeaderTextColor)
{
    m_weakHeaderTextColor = weakHeaderTextColor;
    update( weakHeaderRect() );
}

void TrainingCalendar::dayNumberTextColor(const QColor &dayNumberTextColor)
{
    m_dayNumberTextColor = dayNumberTextColor;
    update( daysViewPortRect() );
}

void TrainingCalendar::setCurrDayNumberTextColor(const QColor& currDayTextColor)
{
    m_currDayNumberTextColor = currDayTextColor;
    update( daysViewPortRect() );
}

void TrainingCalendar::setCurrMonth(const QDate &currMonth)
{
    m_currMonth.setDate( currMonth.year(), currMonth.month(), 1 );
    m_cellRects = calcCellRects( m_currMonth );
    update();
}

void TrainingCalendar::setMonthHeaderFont(const QFont &monthHeaderFont)
{
    m_monthHeaderFont = monthHeaderFont;
    update( monthHeaderRect() );
}

void TrainingCalendar::setMonthHeaderTextColor(const QColor &monthHeaderTextColor)
{
    m_monthHeaderTextColor = monthHeaderTextColor;
    update( monthHeaderRect() );
}

void TrainingCalendar::setCurrYear(int year)
{
    setCurrMonth( QDate( year, currMonth(), 1 ) );
}

void TrainingCalendar::setCurrMonth(int month)
{
    setCurrMonth( QDate( currYear(), month, 1 ) );
}

void TrainingCalendar::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
    update();
}

void TrainingCalendar::setDayNumberTextIndent(const QPoint &dayNumberTextIndent)
{
    m_dayNumberTextIndent = dayNumberTextIndent;
    update();
}

void TrainingCalendar::setDayTextAlign(int dayTextAlign)
{
    m_dayTextAlign = static_cast<Qt::AlignmentFlag>(dayTextAlign);
    update( daysViewPortRect() );
}

void TrainingCalendar::setCurrDayColor(const QColor &currDayColor)
{
    m_currDayColor = currDayColor;
    update( daysViewPortRect() );
}

void TrainingCalendar::drawMonthHeader(QPainter *painter)
{
    drawMonthHeader( painter, m_currMonth, m_drawXDif );
    if( !(m_drawXDif == 0) )
        drawMonthHeader( painter, nextMonth( m_currMonth, m_drawXDif < 0 ), scrollNextIndent() );
}

void TrainingCalendar::drawMonthHeader(QPainter *painter, const QDate &month, int dx)
{
    constexpr std::array month_names = { "Январь", "Февраль",
                                         "Март", "Апрель", "Май",
                                         "Июнь", "Июль", "Август",
                                         "Сентябрь", "Октябрь",
                                         "Ноябрь", "Декабрь" };

    auto rect = monthHeaderRect();
    rect.moveLeft( rect.left() + dx );

    painter->setPen( monthHeaderTextColor() );
    painter->setFont( monthHeaderFont() );
    painter->drawText( rect , Qt::AlignCenter, QString("%1 %2").arg(month_names[static_cast<size_t>(month.month()) - 1]).arg(month.year()) );
}

void TrainingCalendar::drawWeakHeader(QPainter *painter)
{    
    drawWeakHeader( painter, m_drawXDif );
    if( !(m_drawXDif == 0) )
        drawWeakHeader( painter, scrollNextIndent() );
}

void TrainingCalendar::drawWeakHeader(QPainter *painter, int dx)
{
    constexpr std::array day_short_names = { "Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс" };
    constexpr std::array day_names = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресение" };

    painter->setPen( weakHeaderTextColor() );
    painter->setFont( weakHeaderFont() );


    auto UseShortFormat = [&]{
        QFontMetrics metrix( painter->font() );
        for( const auto& name : day_names ) {
            if( metrix.width( name ) >= m_cellRects[0].rect.width() - 8 ) {
                return true;
            }
        }
        return false;
    };

    const auto& text = UseShortFormat() ? day_short_names : day_names;

    for( size_t i = 0, cell = FirstMondayIndexInCellRects(); i < DAY_PER_WEAK; ++i, ++cell )
    {
        QRect text_rect = weakHeaderRect();
        const QRect& cell_rect = m_cellRects[cell].rect;
        text_rect.setLeft( cell_rect.left() );
        text_rect.setRight( cell_rect.right() );
        text_rect.moveLeft( text_rect.left() + dx );
        painter->drawText( text_rect, Qt::AlignCenter, text[i] );
    }
}

void TrainingCalendar::drawDayCells(QPainter *painter)
{   
    drawDayCells( painter, m_cellRects, m_drawXDif );
    if( !(m_drawXDif == 0 || m_scrollCellRects.empty() ) )
        drawDayCells( painter, m_scrollCellRects, scrollNextIndent());
}

void TrainingCalendar::drawDayCells(QPainter *painter, const QVector<DayPaintedData> &cell_rects, int dx)
{
    painter->setPen( Qt::NoPen );
    for( auto& day : cell_rects )
    {
        painter->setBrush( day.backgroundColor );
        QRect rect = day.rect;
        rect.moveLeft( rect.left() + dx );
        painter->drawRect( rect );
    }


    painter->setFont( dayNumberFont() );

    for( auto& day : cell_rects )
    {
        painter->setPen( day.numberColor );
        QRect rect = day.numberRect;
        rect.moveLeft( rect.left() + dx );
        painter->drawText( rect, dayTextAlign(), QString::number( day.number ) );
    }
}

QRect TrainingCalendar::monthHeaderRect() const
{
    return QRect( 0, 0, width(), monthHeaderHeight() );
}

QRect TrainingCalendar::weakHeaderRect() const
{
    return QRect( 0, monthHeaderRect().bottom() + 1, width(), weakHeaderHeight() );
}

Q_ALWAYS_INLINE QRect TrainingCalendar::daysViewPortRect() const
{
    int h_diff = weakHeaderRect().bottom() + 1;
    return QRect( QPoint(0, h_diff), QSize(width(), height() - h_diff ) );
}

QVector<DayPaintedData> TrainingCalendar::calcCellRects(const QDate &month)
{    
    auto cell_width = sizeAndRest( true, DAY_PER_WEAK );
    auto cell_height = sizeAndRest( false, SHOW_WEAK_COUNT );

    QVector< QPair<int, int> > xs( DAY_PER_WEAK );
    QVector< QPair<int, int> > ys( SHOW_WEAK_COUNT );

    xs[0].first = daysViewPortRect().left();
    xs[0].second = xs[0].first + cell_width.first - (cell_width.second ? 0 : 1);
    for( int i = 1; i < DAY_PER_WEAK; ++i )
    {
        xs[i].first = xs[i - 1].second + m_cellIndent + 1;
        xs[i].second = xs[i].first + cell_width.first - (i < cell_width.second ? 0 : 1);
    }

    ys[0].first = daysViewPortRect().top();
    ys[0].second = ys[0].first + cell_height.first - (cell_height.second ? 0 : 1);
    for( int i = 1; i < SHOW_WEAK_COUNT; ++i )
    {
        ys[i].first = ys[i - 1].second + m_cellIndent + 1;
        ys[i].second = ys[i].first + cell_height.first - (i < cell_height.second ? 0 : 1);
    }

    QVector<DayPaintedData> day_cell_rects;
    day_cell_rects.reserve( month.daysInMonth() );

    int day_indent = month.dayOfWeek() - 1;
    bool contains_curr_day = month.month() == QDate::currentDate().month() && month.year() == QDate::currentDate().year();
    int curr_day = QDate::currentDate().day() - 1;

    for( int day = 0; day < month.daysInMonth(); ++day )
    {
        int weak_day = day + day_indent;
        int row = weak_day / DAY_PER_WEAK;
        int col = weak_day - row * DAY_PER_WEAK;

        QPoint top_left( xs[col].first, ys[row].first );
        QPoint bottom_right( xs[col].second, ys[row].second );

        bool is_curr = contains_curr_day && day == curr_day;
        DayPaintedData data{
            QRect( top_left, bottom_right ),
            QRect( top_left + m_dayNumberTextIndent , bottom_right - m_dayNumberTextIndent ),
            is_curr ? currDayColor() : dayColor(),
            is_curr ? currDayNumberTextColor() : dayNumberTextColor(),
            day
        };

        day_cell_rects << data;
    }

    return day_cell_rects;
}

int TrainingCalendar::FirstMondayIndexInCellRects() const
{
    int day_indent = m_currMonth.dayOfWeek() - 1;
    return day_indent == 0 ? 0 : 7 - day_indent;
}


Q_ALWAYS_INLINE QPair<int, int> TrainingCalendar::sizeAndRest(bool width, int parts) const
{
    int full_parts_size = std::max((width ? daysViewPortRect().width() : daysViewPortRect().height()) - (parts - 1) * m_cellIndent , 0 );
    return { full_parts_size / parts , full_parts_size % parts };
}

void TrainingCalendar::scrollMonth(bool right, bool cancel_scroll)
{    
    if( m_scrollAnimation != nullptr )
        return;

    m_scrollAnimation = new QVariantAnimation( this );

    m_scrollAnimation->setStartValue( m_drawXDif );
    m_scrollAnimation->setEndValue( cancel_scroll ? 0 : int(right ? -width() : width()) );

    static const int duration = 250;

    if( cancel_scroll )
    {
        m_scrollAnimation->setDuration( duration * (std::abs(m_drawXDif) / width()) );
        connect( m_scrollAnimation, SIGNAL(finished()), this, SLOT(finishCancelScrollAnimation()) );
    }
    else
    {
        m_scrollAnimation->setDuration( duration * ((width() - std::abs(m_drawXDif)) / width()) );
        connect( m_scrollAnimation, SIGNAL(finished()), this, SLOT(finishScrollAnimation()) );
    }

    connect( m_scrollAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(setDrawXDif(QVariant)) );
    m_scrollAnimation->start();
}

Q_ALWAYS_INLINE int TrainingCalendar::scrollNextIndent() const
{
    return (m_drawXDif < 0 ? width() + m_cellIndent : -width() - m_cellIndent ) + m_drawXDif;
}

void TrainingCalendar::mousePressEvent(QMouseEvent *event)
{
    m_lastMovePoint= event->pos();
    if( m_scrollAnimation != nullptr )
    {
        m_scrollAnimation->stop();
        m_scrollAnimation->deleteLater();
        m_scrollAnimation = nullptr;
    }
}

void TrainingCalendar::mouseMoveEvent(QMouseEvent *event)
{
    if( m_scrollAnimation != nullptr )
        return;

    if( !(m_scrollOn || daysViewPortRect().contains( event->pos() )) )
        return;

    int dif = m_drawXDif + event->pos().x() - m_lastMovePoint.x();
    m_lastMovePoint= event->pos();
    if( std::abs( dif ) > width() + m_cellIndent )
        dif = dif < 0 ? -width() - m_cellIndent : width() + m_cellIndent;

    m_scrollOn = dif != 0;
    if( m_scrollOn )
    {
        if( m_scrollCellRects.empty() )
            m_scrollCellRects = calcCellRects( nextMonth( m_currMonth, dif < 0 ) );
    }
    else
        m_scrollCellRects.clear();

    setDrawXDif( dif );
}

void TrainingCalendar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED( event )
    if( m_scrollOn )
    {
        m_scrollOn = false;
        scrollMonth( m_drawXDif < 0, std::abs( m_drawXDif ) < 50 );
    }
}

void TrainingCalendar::setDrawXDif(const QVariant &value)
{
    setDrawXDif( value.toInt() );
}

void TrainingCalendar::setDrawXDif(int value)
{
    m_drawXDif = value;
    update();
}
void TrainingCalendar::finishScrollAnimation()
{
    setCurrMonth( nextMonth( m_currMonth, m_drawXDif < 0 ) );
    finishCancelScrollAnimation();
}

void TrainingCalendar::finishCancelScrollAnimation()
{
    m_scrollAnimation->stop();
    m_scrollAnimation->deleteLater();
    m_scrollAnimation = nullptr;
    m_scrollCellRects.clear();
    setDrawXDif( 0 );
}

QDate TrainingCalendar::nextMonth(const QDate &from, bool next)
{
    if( next )
        return from.month() == 12 ? QDate( from.year() + 1, 1, 1 ) : QDate( from.year(), from.month() + 1, 1 );
    return from.month() == 1 ? QDate( from.year() - 1, 12, 1 ) : QDate( from.year(), from.month() - 1, 1 );
}

void TrainingCalendar::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if( newGeometry != oldGeometry )
    {        
        m_cellRects = calcCellRects( m_currMonth );
    }
    QQuickPaintedItem::geometryChanged( newGeometry, oldGeometry );
}
