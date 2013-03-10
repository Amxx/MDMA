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
	_hs = new HotSpot(this);
	_hs->resize(5,5);
	QObject::connect(&appCore().cfg, SIGNAL(tabChanged(int)), this, SLOT(update()));
	QObject::connect(&_zn, SIGNAL(updated()), this, SLOT(update()));
	QObject::connect(&_zn, SIGNAL(destroyed()), this, SLOT(deleteLater()));
	QObject::connect(_hs, SIGNAL(mousePress(QMouseEvent*, bool)), this, SLOT(mousePressEvent(QMouseEvent*, bool)));
	QObject::connect(_hs, SIGNAL(mouseRelease(QMouseEvent*, bool)), this, SLOT(mouseReleaseEvent(QMouseEvent*)));
	QObject::connect(_hs, SIGNAL(mouseMove(QMouseEvent*, bool)), this, SLOT(mouseMoveEvent(QMouseEvent*)));
	update();
}
ZoneDrager::~ZoneDrager()
{
	delete _hs;
}

/*
 * ##################################################################################
 * #									SLOTS										#
 * ##################################################################################
 */

void ZoneDrager::mousePressEvent(QMouseEvent *e)
{
	mousePressEvent(e, false);
}
void ZoneDrager::mousePressEvent(QMouseEvent *e, bool hs)
{
	raise();
	switch(e->button())
	{
		case Qt::LeftButton:
		{
			_pos = e->globalPos();
			_move = hs ? RESIZE : DRAG;
			break;
		}
		case Qt::RightButton:
		{
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
		}
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
	if(_move == UNDEFINED)
	{
		_pos = e->globalPos();
		_move = ((e->globalPos() - mapToGlobal(geometry().bottomRight())).manhattanLength() < 5) ? RESIZE : DRAG;
	}
	QPoint delta;
	switch(_move)
	{
		case DRAG:
			delta = e->globalPos() - _pos;
			move(x()+delta.x(), y()+delta.y());
			_pos += delta;
			break;
		case RESIZE:
			delta = e->globalPos() - _pos;
			delta.setX(std::max(delta.x(), 5 - width()));
			delta.setY(std::max(delta.y(), 5 - height()));
			resize(width()+delta.x(), height()+delta.y());
			_pos += delta;
			break;
		default:
			break;
	}
	_zn._geo = geometry();
}
void ZoneDrager::resizeEvent(QResizeEvent *)
{
	_hs->move(width() - _hs->width(), height()-_hs->height());
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
