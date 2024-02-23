#ifndef INPUT_LINE_EDIT_H
#define INPUT_LINE_EDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class InputLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    InputLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

signals:
    void signal_key_input_edit(QString& text);

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        QString text = event->text();
        emit signal_key_input_edit(text);


        // Передаем событие базовому классу для обработки стандартным образом
        //QLineEdit::keyPressEvent(event);
    }
};

#endif // INPUT_LINE_EDIT_H
