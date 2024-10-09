#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

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

    bool sound_Status;

    int min_Datapoints = 100;
    int max_Datapoints = 50000;
    int inc_Datapoints = 0;
    int input_Datapoints;
    int input_MaxValue;
    int datapoint_Values[50000];
    int datapoint_Inc;

    void writeWavFile(const std::vector<float>& samples, const QString& outputPath, int sampleRate);
    void viewChart(QChartView* chartview, QLineSeries* series, QChart* chart, QValueAxis* y, QValueAxis* x);
    void appendChart(QLineSeries* series);
    void drawTimelapseCircle();

private slots:

    void on_btn_OpenFile_clicked();

    void on_btn_ExportFile_clicked();

    void on_dial_Volume_valueChanged(int value);

    void on_btn_Play_clicked();

    void on_btn_Stop_clicked();

    void on_btn_Pause_clicked();

    void on_btn_Chart_clicked();

private:
    Ui::MainWindow *ui;

    QSoundEffect* soundEffect;

    QString filePath;

    QLineSeries *series = new QLineSeries();
    QChart *chart = new QChart();
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    QChartView *chartView = new QChartView(chart);

    float xpos;
    float ypos;
};
#endif // MAINWINDOW_H
