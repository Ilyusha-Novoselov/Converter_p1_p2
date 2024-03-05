#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QTimer>
#include <cctype>

#include "control.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addHistory();

public slots:
    void onButtonClicked();
    void SliderValueChanged(int value);
    void slot_key_input_edit(QString& text);
    void slot_number_changed(std::string& number);

signals:
    void set_focus(bool focus);

private slots:

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    Converter::Control *_control;
};
#endif // MAINWINDOW_H
