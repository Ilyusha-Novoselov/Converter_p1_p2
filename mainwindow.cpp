#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Конвертер");
    _control = new Converter::Control;
    _previousValueSlider = 10;

    connect(ui->Edit_1, &InputLineEdit::signal_key_input_edit, this, &MainWindow::slot_key_input_edit);
    connect(_control, &Converter::Control::signal_number_changed, this, &MainWindow::slot_number_changed);

    QList<QPushButton *> buttons = findChildren<QPushButton *>();
    for (QPushButton *button : buttons)
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
    ui->Button_Comma->setEnabled(false);
    ui->Button_Execut->setEnabled(false);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels({"P1", "Input", "P2", "Output"});
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QString htmlText = R"(
        <html>
            <body style='white-space: pre; font-family: "Courier New", Courier, monospace; font-size: 12pt;'>
<b>Конвертер p1 p2:</b>

<b>Функции кнопок:</b>
-[0-F] Ввод в нужной с.сч.
-BS удалить символ справа
-CE очистить поле ввода
-. разделитель
-= вычислить результат

<b>Функции ползунков:</b>
-Выбор с.сч. от 2 до 16

<b>Клавиатура:</b>
-Доступен ввод только для сим-
волов [0-F] и [.]

<b>История:</b>
-P1 - с.сч. исходного числа
-Input - исходное число
-P2 - с.сч. итогового числа
-Output - итоговое число
            </body>
        </html>)";
    ui->textEdit->setHtml(htmlText);
}

MainWindow::~MainWindow()
{
    delete _control;
    delete ui;
}

void MainWindow::addHistory()
{
    auto history = _control->get_history();
    if(!history.empty())
    {
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(history.rbegin()->p_1)));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(history.rbegin()->number_1)));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(history.rbegin()->p_2)));
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::fromStdString(history.rbegin()->number_2)));
    }
}

void MainWindow::onButtonClicked()
{
    QString text = qobject_cast<QPushButton *>(sender())->text();
    if (text == "=")
    {
        ui->Edit_2->setText(QString::fromStdString(_control->DoCommand(20)));
        addHistory();
    }
    else if(text == "CE")
    {
        QString number = QString::fromStdString(_control->DoCommand(19));
        ui->Edit_1->setText(number);
        ui->Edit_2->setText(number);
    }
    else if(text == "BS")
    {
        ui->Edit_1->setText(QString::fromStdString(_control->DoCommand(18)));
        ui->Edit_2->setText("");
    }
    else if(text == ".")
        ui->Edit_1->setText(QString::fromStdString(_control->DoCommand(17)));
    else
        ui->Edit_1->setText(QString::fromStdString(_control->DoCommand(Converter::Converter_P_10::char_to_num(text[0].toLatin1()))));
}

void MainWindow::SliderValueChanged(int value)
{
    if(qobject_cast<QSlider *>(sender())->objectName() == "Slider_1")
    {
        _control->set_Pin(value);
        if(value < _previousValueSlider)
        {
            QString number = QString::fromStdString(_control->DoCommand(19));
            ui->Edit_1->setText(number);
            ui->Edit_2->setText(number);
        }
        else
        {
            QString result = QString::fromStdString(_control->DoCommand(20));
            ui->Edit_2->setText(result);
            addHistory();
        }
        ui->Edit_p1->setText(QString::number(value));


        QList<QPushButton *> buttons = findChildren<QPushButton *>();
        for (QPushButton *button : buttons)
        {
            QString str = button->text();
            ushort unicodeValue = str[0].unicode();
            wchar_t wchar = unicodeValue;
            char ch = static_cast<char>(wchar);
            int j = Converter::Converter_P_10::char_to_num(ch);
            if(button->text() != "0" && button->text() != "." && button->text() != "=")
            {
                if(j >= 1 && j <= 15 && j >= _control->get_Pin() && button->text() != "BS" && button->text() != "CE")
                    button->setEnabled(false);
                else
                    button->setEnabled(true);
            }
        }
        _previousValueSlider = value;
    }
    if(qobject_cast<QSlider *>(sender())->objectName() == "Slider_2")
    {
        _control->set_Pout(value);
        ui->Edit_p2->setText(QString::number(value));
        if(_control->get_state() == Converter::Converted)
        {
            QString result = QString::fromStdString(_control->DoCommand(20));
            if(result[0] != '.')
            {
                ui->Edit_2->setText(result);
                addHistory();
            }
        }
    }
}

void MainWindow::slot_key_input_edit(QString &text)
{
    if(text == "\r")
    {
        ui->Edit_2->setText(QString::fromStdString(_control->DoCommand(20)));
        addHistory();
        return;
    }
    if(text == ".")
    {
        ui->Edit_1->setText(QString::fromStdString(_control->DoCommand(17)));
        return;
    }
    if(text == "\b")
    {
        ui->Edit_1->setText(QString::fromStdString(_control->DoCommand(18)));
        return;
    }
    ushort unicodeValue = text[0].unicode();
    wchar_t wchar = unicodeValue;
    char ch = static_cast<char>(wchar);
    if (ch >= 'a' && ch <= 'z')
        ch = toupper(ch);
    ui->Edit_1->setText(QString::fromStdString(_control->DoCommand(Converter::Converter_P_10::char_to_num(ch))));
}

void MainWindow::slot_number_changed(std::string& number)
{
    if(_control->get_state() == Converter::Editing)
        ui->Edit_2->setText("");
    if(number.empty() || number.find('.') != std::string::npos)
        ui->Button_Comma->setEnabled(false);
    else
        ui->Button_Comma->setEnabled(true);

    if(number.empty())
        ui->Button_Execut->setEnabled(false);
    else
        ui->Button_Execut->setEnabled(true);
}
