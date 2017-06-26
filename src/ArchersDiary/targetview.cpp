#include "targetview.h"

TargetView::TargetView(QQuickItem *parent)
    : QQuickPaintedItem( parent )
{

}

ShowType TargetView::showType() const
{
    return m_showType;
}

void TargetView::setShowType(ShowType showType)
{
    m_showType = showType;
}

double Shot::length() const
{
    return m_length;
}

void Shot::setLength(double length)
{
    m_length = length;
}

double Shot::aplha() const
{
    return m_aplha;
}

void Shot::setAplha(double aplha)
{
    m_aplha = aplha;
}


void TargetView::touchEvent(QTouchEvent *event)
{
}

void TargetView::paint(QPainter *painter)
{
}
