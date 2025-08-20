#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stopwatch(new StopWatch())
{
    ui->setupUi(this);

    //QLineEdit* time_counter = new QLineEdit();
    time_counter = new QLineEdit();
    QFont font = QFont();
    font.setPointSize(20);
    font.setBold(true);
    time_counter->setFont(font);
    time_counter->setReadOnly(true);
    QLabel* lab = new QLabel("Время");

    //QTextBrowser* txtbrow = new QTextBrowser;
    txtbrow = new QTextBrowser;

    QPushButton* startstop_but = new QPushButton("Старт");
    startstop_but->setCheckable(true);
    startstop_but->setStyleSheet(
        "QPushButton:checked{background-color:yellow;}"
        );
    connect(startstop_but, &QPushButton::toggled, startstop_but, [=](){
        if(startstop_but->isChecked()) startstop_but->setText("Стоп");
        else startstop_but->setText("Старт");
    });
    QPushButton* clear_but = new QPushButton("Очистить");
    QPushButton* lap_but = new QPushButton("Круг");
    lap_but->setEnabled(false);

    QVBoxLayout* time_layout = new QVBoxLayout;
    time_layout->addWidget(lab);
    time_layout->addWidget(time_counter);
    time_layout->setAlignment(Qt::AlignTop);

    QHBoxLayout* txt_layout = new QHBoxLayout;
    QHBoxLayout* but_layout = new QHBoxLayout;

    txt_layout->addLayout(time_layout);
    txt_layout->addWidget(txtbrow);

    but_layout->addWidget(startstop_but);
    but_layout->addWidget(clear_but);
    but_layout->addWidget(lap_but);

    QVBoxLayout* outer_layout = new QVBoxLayout;

    outer_layout->addLayout(txt_layout);
    outer_layout->addLayout(but_layout);

    QWidget* cntrW = new QWidget;
    cntrW->setLayout(outer_layout);
    //cntrW->setStyleSheet("QWidget{background-color:light-blue;}");

    this->setCentralWidget(cntrW);
    this->setWindowTitle("Секундомер");

    //stopwatch = new StopWatch;

    connect(stopwatch, &StopWatch::send_time_update, this, &MainWindow::get_time_update);

    connect(startstop_but, &QPushButton::clicked, this, [=](){
        if(startstop_but->isChecked()){
            lap_but->setEnabled(true);
            stopwatch->start();
        }else{
            lap_but->setEnabled(false);
            stopwatch->stop();
        }
    });

    connect(clear_but, &QPushButton::clicked, stopwatch, &StopWatch::clear);

    connect(stopwatch, &StopWatch::send_lap_update, this, &MainWindow::get_lap_update);

    connect(lap_but, &QPushButton::clicked, stopwatch, &StopWatch::get_lap_info_request);
}

void MainWindow::get_time_update(qint64 time_diff){
    QTime timestamp = QTime::fromMSecsSinceStartOfDay(time_diff);
    time_counter->setText(timestamp.toString("hh:mm:ss:zzz"));
}
void MainWindow::get_lap_update(QString lap_info){
    if(lap_info != "") txtbrow->append(lap_info);
    else txtbrow->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete time_counter;
    delete txtbrow;
    delete stopwatch;
}
