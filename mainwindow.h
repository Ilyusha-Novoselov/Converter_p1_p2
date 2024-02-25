#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cctype>

#include "control.h"
#include "input_line_edit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onButtonClicked();
    void SliderValueChanged(int value);
    void slot_key_input_edit(QString& text);
    void slot_number_changed(std::string& number);

private slots:

private:
    Ui::MainWindow *ui;
    Converter::Control *_control;
    int _previousValueSlider;
};
#endif // MAINWINDOW_H
