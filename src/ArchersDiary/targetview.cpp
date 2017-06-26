#include "targetview.h"

TargetView::TargetView(QQuickItem *parent)
    : QQuickPaintedItem( parent )
{

}

TargetView::ShowType TargetView::showType() const
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

double Shot::alpha() const
{
    return m_alpha;
}

void Shot::setAlpha(double aplha)
{
    m_alpha = aplha;
}
