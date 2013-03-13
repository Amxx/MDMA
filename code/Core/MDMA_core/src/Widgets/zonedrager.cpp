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
		_hs[i] = new HotSpot(i, this);
		_hs[i]->resize(5,5);
		QObject::connect(_hs[i], SIGNAL(mousePress(QMouseEvent*, int)), this, SLOT(mousePressEvent(QMouseEvent*, int)));
		QObject::connect(_hs[i], SIGNAL(mouseRelease(QMouseEvent*, int)), this, SLOT(mouseReleaseEvent(QMouseEvent*)));
		QObject::connect(_hs[i], SIGNAL(mouseMove(QMouseEvent*, int)), this, SLOT(mouseMoveEvent(QMouseEvent*)));

	}
	setGeometry(_zn._geo);
	update();
}
ZoneDrager::~ZoneDrager()
{
	for(int i = 0; i < 4; i++)
		delete _hs[i];
}

/*
 * ##################################################################################
 * #									MOUSE SLOTS									#
 * ##################################################################################
 */

void ZoneDrager::mousePressEvent(QMouseEvent *e)
{
	mousePressEvent(e, NONE);
}
void ZoneDrager::mousePressEvent(QMouseEvent *e, int c)
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
				case S|E:
					_pos = geometry().topLeft();
					_move = RESIZE;
					_moveVar = _zn._var;
					break;
				case N|E:
					_pos = geometry().bottomLeft();
					_move = RESIZE;
					_moveVar = (_zn._var+1)%4;
					break;
				case N|W:
					_pos = geometry().bottomRight();
					_move = RESIZE;
					_moveVar = (_zn._var+2)%4;
					break;
				case S|W:
					_pos = geometry().topRight();
					_move = RESIZE;
					_moveVar = (_zn._var+3)%4;
					break;
			}
			break;
		case Qt::RightButton:
			switch(EditZone(_zn))
			{
				case QDialog::Accepted:
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
		case Qt::MiddleButton:
			if(_zn._type == MDMA::SEGMENT)
			{
				_zn._var += 1;
				_zn._var %= 4;

				appCore().cfg.edited();
				update();
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

	switch(_zn._type)
	{
		case MDMA::NONE:
			_zn._type = MDMA::FADER;
			switch(EditZone(_zn))
			{
				case QDialog::Accepted:
					appCore().cfg.edited();
					break;
				default:
					appCore().cfg.removeZone(_zn);
					break;
			}
			break;

		case MDMA::FADER:
			break;
		case MDMA::PAD:
			break;
		case MDMA::SEGMENT:
			updateHS();
			break;
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
			if(_zn._type == MDMA::SEGMENT)
			{
				_zn._var = _moveVar;
				if(_current.x() < _pos.x() && _current.y() >= _pos.y()) _zn._var += 1;
				if(_current.x() >= _pos.x() && _current.y() < _pos.y()) _zn._var += 3;
				if(_current.x() < _pos.x() && _current.y() < _pos.y()) _zn._var += 2;
				_zn._var %= 4;
			}
			break;
		}
		case UNDEFINED:
			break;
	}
	_zn._geo = geometry();
}

/*
 * ##################################################################################
 * #								CHANGE EVENTS									#
 * ##################################################################################
 */

void ZoneDrager::resizeEvent(QResizeEvent *)
{
	_hs[N|E]->move(width() - _hs[N|W]->width(), 0);
	_hs[S|W]->move(0, height()-_hs[S|W]->height());
	_hs[S|E]->move(width() - _hs[S|E]->width(), height()-_hs[S|E]->height());
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
 * #									UPDATE										#
 * ##################################################################################
 */

void ZoneDrager::update()
{
	setVisible(_zn._tab == appCore().cfg.getTab());
	updateHS();
	switch(_zn._type)
	{
		case MDMA::NONE:
			setStyleSheet("border-radius: 2px; background-color: rgba(255, 255, 78, 128);");
			break;
		case MDMA::FADER:
			setStyleSheet("border-radius: 2px; background-color: rgba(167, 78, 255, 128);");
			break;
		case MDMA::PAD:
			setStyleSheet("border-radius: 2px; background-color: rgba(78, 98, 255, 128);");
			break;
		case MDMA::SEGMENT:
			setStyleSheet("");
			break;
	}
}
void ZoneDrager::updateHS()
{
	switch(_zn._type)
	{
		case MDMA::NONE:
		case MDMA::FADER:
		case MDMA::PAD:
			_hs[0]->show();
			_hs[1]->show();
			_hs[2]->show();
			_hs[3]->show();
			break;
		case MDMA::SEGMENT:
			_hs[0]->setVisible(_zn._var == 0 || _zn._var == 2);
			_hs[3]->setVisible(_zn._var == 0 || _zn._var == 2);
			_hs[1]->setVisible(_zn._var == 1 || _zn._var == 3);
			_hs[2]->setVisible(_zn._var == 1 || _zn._var == 3);
			break;
	}
}

/*
 * ##################################################################################
 * #									DISPLAY										#
 * ##################################################################################
 */

void ZoneDrager::paintEvent(QPaintEvent *)
{
	QPainter pt(this);
	switch(_zn._type)
	{
		case MDMA::NONE:
			break;

		case MDMA::FADER:
			pt.setPen(QPen(QBrush(Qt::red), 2, Qt::SolidLine, Qt::SquareCap));
			if(MDMA::isMidi(_zn[MDMA::EVENT_X].type))
			{
				int x = width() * _zn[MDMA::EVENT_X].signal[_zn[MDMA::EVENT_X].variable] / 127;
				pt.drawLine(QPoint(x, 0), QPoint(x, height()));
			}
			if(MDMA::isMidi(_zn[MDMA::EVENT_Y].type))
			{
				int y = height() - height() * _zn[MDMA::EVENT_Y].signal[_zn[MDMA::EVENT_Y].variable] / 127;
				pt.drawLine(QPoint(0, y), QPoint(width(), y));
			}
			break;

		case MDMA::PAD:
			break;

		case MDMA::SEGMENT:
		{
			QPoint pos[2];

			switch(_zn._var)
			{
				case 0:
					pos[0] = QPoint(0,0);
					pos[1] = QPoint(width(), height());
					break;
				case 1:
					pos[0] = QPoint(width(), 0);
					pos[1] = QPoint(0, height());
					break;
				case 2:
					pos[0] = QPoint(width(), height());
					pos[1] = QPoint(0,0);
					break;
				case 3:
					pos[0] = QPoint(0, height());
					pos[1] = QPoint(width(), 0);
					break;
				default:
					throw "[ ZoneDrager::painEvent ] _zn._var out of bound";
					break;
			}

			QPoint center, director;
			center = (pos[0]+pos[1])/2;
			director = pos[0]-pos[1];
			director *= 10/sqrt(director.x()*director.x()+director.y()*director.y());

			QPolygon poly;
			poly << pos[0];
			poly << center + director;
			poly << center + sqrt(3)*QPoint(-director.y(), director.x());
			poly << center - director;
			poly << pos[1];

			pt.setPen(QPen(QBrush(QColor(78, 167, 255, 128)), 1, Qt::SolidLine, Qt::RoundCap));
			pt.setBrush(QBrush(QColor(78, 167, 255, 128)));
			pt.drawPolygon(poly);
			break;
		}
	}
	pt.end();

}
