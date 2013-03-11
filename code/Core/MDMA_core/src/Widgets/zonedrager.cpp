#include "zonedrager.h"

/*
 * ##################################################################################
 * #								CONSTRUCTORS									#
 * ##################################################################################
 */

ZoneDrager::ZoneDrager(Zone& zn, QWidget* parent, Qt::WindowFlags f):
	QLabel(parent, f),
	_zn(zn)
{
	QObject::connect(&appCore().cfg, SIGNAL(tabChanged(int)), this, SLOT(update()));
	QObject::connect(&_zn, SIGNAL(updated()), this, SLOT(update()));
	QObject::connect(&_zn, SIGNAL(destroyed()), this, SLOT(deleteLater()));
	for(int i = 0; i < 4; i++)
	{
		_hs[i] = new HotSpot((corner) i, this);
		_hs[i]->resize(5,5);
		QObject::connect(_hs[i], SIGNAL(mousePress(QMouseEvent*, corner)), this, SLOT(mousePressEvent(QMouseEvent*, corner)));
		QObject::connect(_hs[i], SIGNAL(mouseRelease(QMouseEvent*, corner)), this, SLOT(mouseReleaseEvent(QMouseEvent*)));
		QObject::connect(_hs[i], SIGNAL(mouseMove(QMouseEvent*, corner)), this, SLOT(mouseMoveEvent(QMouseEvent*)));

	}
	update();
}
ZoneDrager::~ZoneDrager()
{
	delete _hs[0];
	delete _hs[1];
	delete _hs[2];
	delete _hs[3];
}

/*
 * ##################################################################################
 * #									SLOTS										#
 * ##################################################################################
 */

void ZoneDrager::mousePressEvent(QMouseEvent *e)
{
	mousePressEvent(e, NONE);
}
void ZoneDrager::mousePressEvent(QMouseEvent *e, corner c)
{
	raise();
	switch(e->button())
	{
		case Qt::LeftButton:
			switch(c)
			{
				case NONE:
					_pos = e->globalPos();
					_move = DRAG;
					break;
				case NW:
					_pos = geometry().bottomRight();
					_move = RESIZE;
					break;
				case NE:
					_pos = geometry().bottomLeft();
					_move = RESIZE;
					break;
				case SE:
					_pos = geometry().topLeft();
					_move = RESIZE;
					break;
				case SW:
					_pos = geometry().topRight();
					_move = RESIZE;
					break;
			}
			break;
		case Qt::RightButton:
			switch(EditZone(_zn))
			{
				case QDialog::Accepted:
					update();
					appCore().cfg.edited();
					break;
				case -1:
					appCore().cfg.removeZone(_zn);
					appCore().cfg.edited();
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
void ZoneDrager::mouseReleaseEvent(QMouseEvent*)
{
	setCursor(Qt::OpenHandCursor);
	QApplication::processEvents();
	if(_zn._type == MDMA::NONE)
	{
		_zn._type = MDMA::FADER;
		switch(EditZone(_zn))
		{
			case QDialog::Accepted:
				update();
				appCore().cfg.edited();
				break;
			default:
				appCore().cfg.removeZone(_zn);
				break;
		}
	}
	_move = UNDEFINED;
}
void ZoneDrager::mouseMoveEvent(QMouseEvent *e)
{
	QPoint delta;
	switch(_move)
	{
		case DRAG:
		{
			delta = e->globalPos() - _pos;
			move(x()+delta.x(), y()+delta.y());
			_pos = e->globalPos();
			break;
		}
		case RESIZE:
		{
			QPoint _current = appCore().Ui()->mapFromGlobal(e->globalPos());
			int x = qMin(_pos.x(), _current.x());
			int y = qMin(_pos.y(), _current.y());
			int w = abs(_pos.x() - _current.x());
			int h = abs(_pos.y() - _current.y());
			setGeometry(x, y, w, h);
			break;
		}
		case UNDEFINED:
			break;
	}
	_zn._geo = geometry();
}
void ZoneDrager::resizeEvent(QResizeEvent *)
{
	_hs[NE]->move(width() - _hs[NW]->width(), 0);
	_hs[SE]->move(width() - _hs[NW]->width(), height()-_hs[NW]->height());
	_hs[SW]->move(0, height()-_hs[NW]->height());
	if(_zn._type != MDMA::NONE) appCore().cfg.edited();
}
void ZoneDrager::moveEvent(QMoveEvent *)
{
	if(_zn._type != MDMA::NONE) appCore().cfg.edited();
}
void ZoneDrager::enterEvent(QEvent *)
{
	setCursor(Qt::OpenHandCursor);
	QApplication::processEvents();
}
void ZoneDrager::leaveEvent(QEvent *)
{
}

/*
 * ##################################################################################
 * #									DISPLAY										#
 * ##################################################################################
 */

void ZoneDrager::update()
{
	setVisible(_zn._tab == appCore().cfg.getTab());
	switch(_zn._type)
	{
		case MDMA::NONE:
			setGeometry(_zn._geo);
			setFrameStyle(QFrame::Box);
			setStyleSheet("border-radius: 2px; background-color: rgba(255, 255, 78, 128);");
			break;
		case MDMA::FADER:
			setGeometry(_zn._geo);
			setFrameStyle(QFrame::Box);
			setStyleSheet("border-radius: 2px; background-color: rgba(167, 78, 255, 128);");
			break;
		case MDMA::PAD:
			setGeometry(_zn._geo);
			setFrameStyle(QFrame::Box);
			setStyleSheet("border-radius: 2px; background-color: rgba(78, 98, 255, 128);");
			break;
		case MDMA::SEGMENT:
			setGeometry(_zn._geo);
			setFrameStyle(QFrame::Box);
			setStyleSheet("border-radius: 2px; background-color: rgba(78, 167, 255, 128);");
			break;
	}
}
