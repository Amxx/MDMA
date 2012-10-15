#ifndef LOG_H
#define LOG_H

#include <QObject>

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = 0);
    
signals:
    
public slots:
    void receive_detection(int id, int valeur);
};

#endif // LOG_H
