#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Edit_1, &InputLineEdit::signal_key_input_edit, this, &MainWindow::slot_key_input_edit);

    // Проход по всем созданным кнопкам
    QList<QPushButton *> buttons = findChildren<QPushButton *>();
    for (QPushButton *button : buttons)
        // Подключение сигнала clicked() каждой кнопки к слоту нажатия кнопки
        connect(button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    QList<QSlider *> sliders = findChildren<QSlider *>();
    for (QSlider *slider : sliders)
    {
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(SliderValueChanged(int)));
        slider->setRange(2, 16);
        slider->setSingleStep(1);
        slider->setPageStep(1);
        slider->setValue(10);
        slider->setTickPosition(QSlider::TicksBelow);
        slider->setTickInterval(1);
    }
    ui->Slider_2->setValue(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked()
{
    QString text = qobject_cast<QPushButton *>(sender())->text();
    if (text == "=")
        ui->Edit_2->setText(QString::fromStdString(_control.DoCommand(20)));
    else
        if(text == "CE")
            ui->Edit_1->setText(QString::fromStdString(_control.DoCommand(19)));
        else
            if(text == "BS")
                ui->Edit_1->setText(QString::fromStdString(_control.DoCommand(18)));
            else
                if(text == ".")
                    ui->Edit_1->setText(QString::fromStdString(_control.DoCommand(17)));
                else
                    ui->Edit_1->setText(QString::fromStdString(_control.DoCommand(Converter::Converter_P_10::char_to_num(text[0].toLatin1()))));
}

void MainWindow::SliderValueChanged(int value)
{
    if(qobject_cast<QSlider *>(sender())->objectName() == "Slider_1")
    {
        ui->Edit_p1->setText(QString::number(value));
        _control.set_Pin(value);

        QList<QPushButton *> buttons = findChildren<QPushButton *>();
        for (QPushButton *button : buttons)
        {
            ushort unicodeValue = button->text()[0].unicode();
            wchar_t wchar = unicodeValue;
            char ch = static_cast<char>(wchar);
            int j = Converter::Converter_P_10::char_to_num(ch);
            if(j >= 1 && j <= 15 && j >= _control.get_Pin() && button->text() != "BS" && button->text() != "CE")
                button->setEnabled(false);
            else
                button->setEnabled(true);
        }
    }
    if(qobject_cast<QSlider *>(sender())->objectName() == "Slider_2")
    {
        ui->Edit_p2->setText(QString::number(value));
        _control.set_Pout(value);
        QString result = QString::fromStdString(_control.DoCommand(20));
        if(result[0] != '.')
            ui->Edit_2->setText(result);
    }
}

void MainWindow::slot_key_input_edit(QString &text)
{
    if(text == ".")
        ui->Edit_1->setText(QString::fromStdString(_control.DoCommand(17)));

    ushort unicodeValue = text[0].unicode();
    wchar_t wchar = unicodeValue;
    char ch = static_cast<char>(wchar);
    if (ch >= 'a' && ch <= 'z')
        ch = toupper(ch);
    ui->Edit_1->setText(QString::fromStdString(_control.DoCommand(Converter::Converter_P_10::char_to_num(ch))));
}
