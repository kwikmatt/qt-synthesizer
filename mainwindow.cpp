/*fix crash issue -- application crashing when opening larger .csv files
 * trying utilizin an array to fix crash issue, store the data values first then plot them?
 * fix export, high prio
 * add timelapse circle to chart (later)
*/
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QIcon>
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>
#include <QAudioFormat>
#include <QTextStream>
#include <QMessageBox>
#include <QDataStream>
#include <QFile>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtMath>
#include <QBoxLayout>
#include <QGraphicsEllipseItem>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), sound_Status(true), xpos(0), ypos(0)
{
    ui->setupUi(this);

    series = new QLineSeries();
    chart = new QChart();
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    chartView = new QChartView(chart);

    this->setStyleSheet("background-color: rgb(38, 38, 41);");
    this->setWindowTitle("Wave Table Synthesizer");

    ui->cb_BitDepth->setStyleSheet("background-color: green; color: white");
    ui->cb_SampleRate->setStyleSheet("background-color: green; color: white");
    ui->lbl_SampleRate->setStyleSheet("color: white;");
    ui->lbl_BitDepth->setStyleSheet("color: white;");
    ui->lbl_Volume->setStyleSheet("color: white;");
    ui->lbl_Title->setStyleSheet("color: white;");
    ui->lbl_DataPoint->setStyleSheet("color: white;");
    ui->lbl_MaxValue->setStyleSheet("color: white;");
    ui->fr_Controls->setStyleSheet("background-color: rgb(27, 28, 31);");
    ui->fr_Macro2->setStyleSheet("background-color: rgb(27, 28, 31);");
    ui->fr_Buttons->setStyleSheet("background-color: rgb(27, 28, 31);");
    ui->fr_Files->setStyleSheet("background-color: rgb(27, 28, 31);");
    ui->fr_Chart->setStyleSheet("background-color: rgb(27, 28, 31);");
    ui->lcd_Volume->setStyleSheet("background-color: green");
    ui->btn_Stop->setStyleSheet("background-color: green; color: white;");
    ui->btn_Play->setStyleSheet("background-color: green; color: white;");
    ui->btn_Pause->setStyleSheet("background-color: green; color: white;");
    ui->btn_Chart->setStyleSheet("background-color: green; color: white;");
    ui->btn_OpenFile->setStyleSheet("background-color: green; color: white;");
    ui->btn_ExportFile->setStyleSheet("background-color: green; color: white;");
    ui->le_DataPoint->setStyleSheet("background-color: white;");
    ui->le_MaxValue->setStyleSheet("background-color: white;");

    soundEffect = new QSoundEffect(this);

    on_dial_Volume_valueChanged(ui->dial_Volume->value());

    ui->lcd_Volume->display(ui->dial_Volume->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::viewChart(QChartView *chartview, QLineSeries *series, QChart *chart, QValueAxis *y, QValueAxis *x){
    //add chart parameters here then call it within the chart button also add button parameters such as setting window size, etc (utilize in line text box so user can input a value (width x height)
    chart->legend()->hide();

    appendChart(series);

    chart->addSeries(series);

    chart->setTitle("Chart");

    x->setRange(0, input_Datapoints);
    x->setTitleText("X Axis");

    y->setRange(0, input_MaxValue);
    y->setTitleText("Y Axis");

    chart->addAxis(x, Qt::AlignBottom);
    chart->addAxis(y, Qt::AlignLeft);

    series->attachAxis(x);
    series->attachAxis(y);

    QMainWindow* chartWindow = new QMainWindow();

    chartWindow->setWindowTitle("Chart Window");

    chartWindow->setCentralWidget(chartview);

    chartWindow->resize(600, 400);

    chartWindow->show();

}

void MainWindow::appendChart(QLineSeries* series){
    series->append(xpos, ypos);
}

void MainWindow::drawTimelapseCircle(){

}

void MainWindow::on_btn_OpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("CSV Files (*.csv);;WAV Files (*.wav)"));

    QMessageBox msgBox;

    msgBox.setStyleSheet("QLabel { color: white; }"
                         "QPushButton { background-color: gray; color: white; }"
                         "QMessageBox { background-color: black; }");

    if (!fileName.isEmpty()) {
        qDebug() << "Selected file:" << fileName;

        // Store the file path for future use
        filePath = fileName;

        QFileInfo fileInfo(fileName);
        QString fileExtension = fileInfo.suffix().toLower();

        if (fileExtension == "csv") {
            // Open and read the CSV file here
            QFile csvFile(filePath);

            if (!csvFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                msgBox.setText("Unable to open CSV file");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.exec();
                return;
            }

            QTextStream in(&csvFile);
            int inc_Datapoints = 0;
            bool invalidDataFound = false;

            xpos = 0; // Reset xpos before reading the file
            series->clear(); // Clear previous chart data

            // Read each line in the CSV
            while (!in.atEnd()) {
                QString line = in.readLine().trimmed(); // Trim whitespace around the line

                // Check if the line is not empty
                if (!line.isEmpty()) {
                    // Remove commas and extra spaces
                    line = line.remove(QRegularExpression("[^0-9\\.-]"));  // Keep only numeric values, periods, or minus signs

                    bool isNumeric;
                    double value = line.toDouble(&isNumeric);  // Try converting to a number

                    if (isNumeric) {
                        ypos = value; // CSV data point is assigned to ypos (Y-axis value)
                        series->append(xpos, ypos); // Plot the point (xpos, ypos)
                        xpos++; // Increment xpos for the next data point
                        inc_Datapoints++;
                        qDebug() << "Data Point (X,Y): (" << xpos-1 << "," << ypos << ")";
                    } else {
                        // Log invalid lines for debugging
                        qDebug() << "Invalid data in CSV: [" << line << "]";
                        invalidDataFound = true;
                    }
                }
            }

            csvFile.close();

            if (!csvFile.isOpen()){
                qDebug() << "File Successfully Closed";
            } else {
                qDebug() << "File Failed to Close";
            }

            if (invalidDataFound) {
                msgBox.setText("CSV file contains invalid data. Check for non-numeric values or wrong formatting.");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.exec();
                return;
            }

            // Check if the number of datapoints is between 100 and 50,000
            if (inc_Datapoints < 100 || inc_Datapoints > 50000) {
                msgBox.setText("CSV file must have between 100 and 50,000 datapoints. Please open another file.");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.exec();
                return;
            }

            qDebug() << "Total Datapoint Count: " << inc_Datapoints;

            // After plotting the data, update the chart
            chart->removeAllSeries(); // Clear previous chart data
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->setTitle("CSV Data Plot");
            axisX->setRange(0, xpos); // Set X-axis range from 0 to number of data points
            axisY->applyNiceNumbers(); // Auto adjust Y-axis based on the values
        } else if (fileExtension == "wav") {
            soundEffect->setSource(QUrl::fromLocalFile(fileName));
            msgBox.setText("WAV file successfully loaded.");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        } else {
            msgBox.setText("Only CSV and WAV files are supported.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
    }
}

void MainWindow::on_btn_ExportFile_clicked()
{
    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel { color: white; }"
                         "QPushButton { background-color: gray; color: white; }"
                         "QMessageBox { background-color: black; }");

    if (filePath.isEmpty()) {
        // No CSV file opened
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("No CSV File Opened. Please open a file first.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        return;
    }

    // Prompt for file name for saving the .wav file
    QString wavFileName = QFileDialog::getSaveFileName(this, tr("Export as WAV"), "", tr("WAV Files (*.wav)"));

    if (wavFileName.isEmpty()) {
        // If the user cancels the save dialog
        return;
    }

    // Ensure the file has a .wav extension
    if (!wavFileName.endsWith(".wav", Qt::CaseInsensitive)) {
        wavFileName += ".wav";
    }

    // Open the file to write the WAV data
    QFile wavFile(wavFileName);
    if (!wavFile.open(QIODevice::WriteOnly)) {
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Unable to create WAV file.");
        msgBox.exec();
        return;
    }

    // WAV file header
    QByteArray wavHeader;
    int sampleRate = 44100;  // Standard sample rate for audio files
    int numChannels = 1;     // Mono
    int bitsPerSample = 16;  // Bit depth (16-bit)

    int numSamples = series->count();  // The number of CSV data points plotted
    int dataSize = numSamples * numChannels * (bitsPerSample / 8);  // Total data size for the WAV file

    // Add RIFF header
    wavHeader.append("RIFF");
    wavHeader.append(reinterpret_cast<const char *>(&dataSize + 36), 4);  // Size of the overall file minus 8 bytes
    wavHeader.append("WAVE");

    // Add fmt chunk
    wavHeader.append("fmt ");
    int fmtChunkSize = 16;
    wavHeader.append(reinterpret_cast<const char *>(&fmtChunkSize), 4);
    short audioFormat = 1;  // PCM format
    wavHeader.append(reinterpret_cast<const char *>(&audioFormat), 2);
    wavHeader.append(reinterpret_cast<const char *>(&numChannels), 2);
    wavHeader.append(reinterpret_cast<const char *>(&sampleRate), 4);
    int byteRate = sampleRate * numChannels * (bitsPerSample / 8);
    wavHeader.append(reinterpret_cast<const char *>(&byteRate), 4);
    short blockAlign = numChannels * (bitsPerSample / 8);
    wavHeader.append(reinterpret_cast<const char *>(&blockAlign), 2);
    wavHeader.append(reinterpret_cast<const char *>(&bitsPerSample), 2);

    // Add data chunk
    wavHeader.append("data");
    wavHeader.append(reinterpret_cast<const char *>(&dataSize), 4);

    // Write the header to the WAV file
    wavFile.write(wavHeader);

    // Write the CSV data (converted to audio samples) into the WAV file
    for (int i = 0; i < series->count(); ++i) {
        QPointF point = series->at(i);  // Get the plotted point
        double sampleValue = point.y();  // Use Y-axis value as the audio sample

        // Scale the sample value to fit into the 16-bit range [-32768, 32767]
        int16_t audioSample = static_cast<int16_t>(sampleValue * 32767);

        // Write the sample to the file (little-endian format)
        wavFile.write(reinterpret_cast<const char *>(&audioSample), sizeof(int16_t));
    }

    wavFile.close();

    // Inform the user of success
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("CSV file successfully exported as WAV.");
    msgBox.exec();
}


void MainWindow::on_dial_Volume_valueChanged(int value)
{
    float volume = value / 100.0f;

    if (soundEffect){
        soundEffect->setVolume(volume);
    }

    ui->lcd_Volume->display(value);
}


void MainWindow::on_btn_Play_clicked()
{
    soundEffect->play();
    soundEffect->setMuted(false);
}


void MainWindow::on_btn_Stop_clicked()
{
    soundEffect->stop();
}


void MainWindow::on_btn_Pause_clicked()
{
    soundEffect->setMuted(true);
}

void MainWindow::on_btn_Chart_clicked()
{
    QString maxValue = ui->le_MaxValue->text();
    QString dataPoints = ui->le_DataPoint->text();
    QMessageBox msgBox;

    msgBox.setStyleSheet("QLabel { color: white; }"
                         "QPushButton { background-color: gray; color: white; }"
                         "QMessageBox { background-color: black; }");

    input_MaxValue = maxValue.toInt();
    input_Datapoints = dataPoints.toInt();

    if (input_MaxValue == 0 || input_Datapoints == 0){
        msgBox.setText("Please Fill Out Both Fields (Max Value and Datapoints)");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    } else {
        viewChart(chartView, series, chart, axisY, axisX);
    }
}

