#include "Draw/cellpainter.h"


draw::CellPainter::CellPainter(QObject* parent): QObject (parent)
{
}

void draw::CellPainter::drawCell(QPainter* painter, const QRectF& rect, bool opened) const
{
    painter->save();

    int x1 = static_cast<int>(rect.x());
    int y1 = static_cast<int>(rect.y());
    int x2 = x1 + static_cast<int>(rect.width());
    int y2 = y1 + static_cast<int>(rect.height());

    painter->setBrush(Qt::gray);

    if (opened) {
        painter->setPen(Qt::darkGray);
        QPainterPath path;
        painter->drawRect(x1, y1, static_cast<int>(rect.width()), static_cast<int>(rect.height()));
        path.moveTo(x1, y1);
        path.lineTo(x1, y2 - 1);
        path.lineTo(x2, y2 - 1);
    } else {
        painter->setPen(Qt::lightGray);
        painter->drawRect(x1, y1, static_cast<int>(rect.width()), static_cast<int>(rect.height()));
        QPainterPath path;
        path.moveTo(x1, y2);
        path.lineTo(x1, y1);
        path.lineTo(x2, y1);

        painter->drawPath(path);

        path.moveTo(x1 + 1, y2 - 1);
        path.lineTo(x1 + 1, y1 + 1);
        path.lineTo(x2 - 1, y1 + 1);
        painter->drawPath(path);

        painter->setPen(Qt::darkGray);
        path = QPainterPath();

        path.moveTo(x1 + 1, y2 - 1);
        path.lineTo(x2 - 1, y2 - 1);
        path.lineTo(x2 - 1, y1);
        painter->drawPath(path);

        path.moveTo(x1 + 2, y2 - 2);
        path.lineTo(x2 - 2, y2 - 2);
        path.lineTo(x2 - 2, y1 + 1);
        painter->drawPath(path);
    }
    painter->restore();
}

void draw::CellPainter::drawColorDigit(QPainter* painter, const QRectF& rect, quint8 digit) const
{
    QColor color;

    switch (digit) {
    case 1:
        color = Qt::blue;
        break;
    case 2:
        color = Qt::darkGreen;
        break;
    case 3:
        color = Qt::red;
        break;
    case 4:
        color = Qt::darkBlue;
        break;
    case 5:
        color = Qt::darkRed;
        break;
    case 6:
        color = Qt::darkGreen;
        break;
    case 7:
        color = Qt::black;
        break;
    case 8:
        color = Qt::darkGray;
        break;
    default:
        return;
    }
    painter->save();
    painter->setPen(color);
    painter->setFont(QFont("Times", 10, QFont::Bold));
    painter->drawText(rect, Qt::AlignCenter, QString::number(digit));

    painter->restore();
}

void draw::CellPainter::drawCross(QPainter* painter, const QRectF& rect) const
{
    painter->save();

    painter->setPen(Qt::red);

    int x1 = static_cast<int>(rect.x());
    int y1 = static_cast<int>(rect.y());
    int x2 = x1 + static_cast<int>(rect.width());
    int y2 = y1 + static_cast<int>(rect.height());

    painter->drawLine(QPoint(x1, y1), QPoint(x2, y2));
    painter->drawLine(QPoint(x2, y1), QPoint(x1, y2));

    painter->restore();
}

void draw::CellPainter::drawFlag(QPainter* painter, const QRectF& rect) const
{
    painter->save();

    const int dist = 4;

    int x = static_cast<int>(rect.x()) + dist;
    int y = static_cast<int>(rect.y()) + dist;
    int width = static_cast<int>(rect.width()) - 2 * dist;
    int height = static_cast<int>(rect.height()) - 2 * dist;

    QPoint a,b,c;
    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);

    a.setX(x + width/2);
    a.setY(y);
    b.setX(a.x());
    b.setY(a.y() + height/2);
    c.setX(x);
    c.setY(y + height/4);
    QPolygon pol;
    pol << a << b << c << a;
    painter->drawPolygon(pol);

    QPoint d, e, f;
    d.setX(a.x());
    d.setY(y + height);
    painter->setPen(Qt::black);
    painter->drawLine(b, d);
    e.setX(d.x() - (b.x() - c.x())/2);
    f.setX(d.x() + (b.x() - c.x())/2);
    e.setY(d.y());
    f.setY(d.y());
    painter->drawLine(e, f);
    painter->restore();
}

void draw::CellPainter::drawMine(QPainter* painter, const QRectF& rect, QColor backgroundColor) const
{
    painter->save();
    painter->fillRect(static_cast<int>(rect.x()) + 1,
                      static_cast<int>(rect.y()) + 1,
                      static_cast<int>(rect.width()) - 1,
                      static_cast<int>(rect.height()) - 1,
                      backgroundColor);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    QPoint center;
    center.setX(static_cast<int>(rect.x() + rect.width()/2));
    center.setY(static_cast<int>(rect.y() + rect.height()/2));
    const quint8 r = 7;
    painter->drawEllipse(center,r,r);

    const QPoint A(center.x() - r - 2, center.y());
    const QPoint B(center.x() + r + 2, center.y());
    painter->drawLine(A, B);
    const QPoint C(center.x(), center.y() - r - 2);
    const QPoint D(center.x(), center.y() + r + 2);
    painter->drawLine(C, D);

    painter->setBrush(Qt::white);
    const quint8 size = 4;
    painter->drawRect(center.x() - size, center.y() - size, size, size);
    painter->restore();
}
