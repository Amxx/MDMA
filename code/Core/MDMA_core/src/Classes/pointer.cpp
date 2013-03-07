#include "pointer.h"

TriPoint::TriPoint() :
	_x(0),
	_y(0),
	_z(0)
{
}
TriPoint::TriPoint(QPoint p) :
	_x(p.x()),
	_y(p.y()),
	_z(0)
{
}
TriPoint::TriPoint(int x, int y, int z) :
	_x(x),
	_y(y),
	_z(z)
{
}
TriPoint::TriPoint(const TriPoint& cpy) :
	_x(cpy._x),
	_y(cpy._y),
	_z(cpy._z)
{
}
int TriPoint::x()
{
	return _x;
}
int TriPoint::y()
{
	return _y;
}
int TriPoint::z()
{
	return _z;
}



TriPointHist::TriPointHist() :
	_cur(TriPoint()),
	_pre(TriPoint())
{
}
TriPointHist::TriPointHist(TriPoint p) :
	_cur(p),
	_pre(p)
{
}
TriPointHist::TriPointHist(const TriPointHist& cpy) :
	_cur(cpy._cur),
	_pre(cpy._pre)
{
}
void TriPointHist::update(TriPoint p)
{
	_pre = _cur;
	_cur = p;
}
TriPoint TriPointHist::current()
{
	return _cur;
}
TriPoint TriPointHist::previous()
{
	return _pre;
}



OnOffHist::OnOffHist() :
	_cur(false),
	_pre(false)
{
}
OnOffHist::OnOffHist(bool s) :
	_cur(s),
	_pre(s)
{
}
OnOffHist::OnOffHist(const OnOffHist& cpy) :
	_cur(cpy._cur),
	_pre(cpy._pre)
{
}
void OnOffHist::update(bool s)
{
	_pre = _cur;
	_cur = s;
}
bool OnOffHist::current()
{
	return _cur;
}
bool OnOffHist::previous()
{
	return _pre;
}



Pointer::Pointer() :
	_pos(TriPointHist()),
	_spe(TriPointHist()),
	_acc(TriPointHist()),
	_onoff(OnOffHist())
{
}
Pointer::Pointer(TriPoint p, bool s) :
	_pos(TriPointHist(p)),
	_spe(TriPointHist()),
	_acc(TriPointHist()),
	_onoff(OnOffHist(s))
{
}
Pointer::Pointer(const Pointer& cpy) :
	_pos(cpy._pos),
	_spe(cpy._spe),
	_acc(cpy._acc),
	_onoff(cpy._onoff)
{
}
void Pointer::update(TriPoint p, bool s)
{
	_pos.update(p);
	_spe.update(_pos.current()-_pos.previous());
	_acc.update(_spe.current()-_spe.previous());
	_onoff.update(s);
}
TriPointHist Pointer::pos()
{
	return _pos;
}
TriPointHist Pointer::spe()
{
	return _spe;
}
TriPointHist Pointer::acc()
{
	return _acc;
}
OnOffHist Pointer::on()
{
	return _onoff;
}
