#ifndef POINTER_H
#define POINTER_H

#include <QPoint>

class TriPoint
{
	public:
		TriPoint();
		TriPoint(QPoint p);
		TriPoint(int x, int y, int z = 0);
		TriPoint(const TriPoint& cpy);
		int x();
		int y();
		int z();
		TriPoint& operator+=( const TriPoint& p ) { _x += p._x; _y += p._y; _z += p._z; return *this;}
		TriPoint operator+( const TriPoint& p ) const { return TriPoint(*this).operator+=(p); }
		TriPoint& operator-=( const TriPoint& p ) { _x -= p._x; _y -= p._y; _z -= p._z; return *this;}
		TriPoint operator-( const TriPoint& p ) const { return TriPoint(*this).operator-=(p); }
	private:
		int _x;
		int _y;
		int _z;
};
class TriPointHist
{
	public:
		TriPointHist();
		TriPointHist(TriPoint p);
		TriPointHist(const TriPointHist& cpy);
		void update(TriPoint p);
		TriPoint current();
		TriPoint previous();
	private :
		TriPoint _cur;
		TriPoint _pre;
};
class OnOffHist
{
	public:
		OnOffHist();
		OnOffHist(bool s);
		OnOffHist(const OnOffHist& cpy);
		void update(bool s);
		bool current();
		bool previous();
	private:
		bool _cur;
		bool _pre;
};

class Pointer
{
	public:
		Pointer();
		Pointer(TriPoint p, bool s = false);
		Pointer(const Pointer& cpy);
		void update(TriPoint p, bool s);
		TriPointHist pos();
		TriPointHist spe();
		TriPointHist acc();
		OnOffHist on();
	private:
		TriPointHist _pos;
		TriPointHist _spe;
		TriPointHist _acc;
		OnOffHist _onoff;
};

#endif // POINTER_H
