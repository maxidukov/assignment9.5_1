#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QTimer>
#include <QTime>

class StopWatch : public QObject
{
    Q_OBJECT
public:
    StopWatch(QObject *parent = nullptr);
    ~StopWatch();

Q_SIGNALS:
    void send_time_update(qint64);
    void send_lap_update(QString);

public Q_SLOTS:
    void start();
    void stop();
    void clear();
    void get_lap_info_request();


private:
    QTimer* timer;
    QTime start_time = QTime::currentTime();
    qint64 time_diff = 0;
    qint64 prev_diff = 0;
    qint64 prev_lap_time = 0;
    qint64 lap = 1;
};

#endif // STOPWATCH_H
