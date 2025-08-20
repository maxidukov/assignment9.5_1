#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QTextBrowser>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QTimer>
#include <QTime>

#include <unistd.h>

#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void get_time_update(qint64);
    void get_lap_update(QString);

private:
    Ui::MainWindow *ui;
    QLineEdit* time_counter;
    QTextBrowser* txtbrow;
    StopWatch* stopwatch;
};
#endif // MAINWINDOW_H
