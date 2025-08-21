#include "stopwatch.h"

StopWatch::StopWatch(QObject *parent): timer(new QTimer()) {
    connect(timer, &QTimer::timeout, this, [&](){
        time_diff = start_time.msecsTo(QTime::currentTime()) + prev_diff;
        emit send_time_update(time_diff);
    });
}

void StopWatch::start(){
    start_time = QTime::currentTime();
    timer->start(100);
}
void StopWatch::stop(){
    prev_diff = time_diff;
    timer->stop();
}
void StopWatch::clear(){
    prev_diff = 0;
    prev_lap_time = 0;
    start_time = QTime::currentTime();
    lap = 1;
    emit send_time_update(0);
    emit send_lap_update("");
}

void StopWatch::get_lap_info_request(){
    QString lap_info = "Круг " + QString::number(lap++);
    lap_info += ", время: " + QString::number((time_diff-prev_lap_time)/1000) + " сек";
    prev_lap_time = time_diff;
    emit send_lap_update(lap_info);
}

StopWatch::~StopWatch(){
    delete timer;
}
