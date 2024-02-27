#ifndef INPUT_LINE_EDIT_H
#define INPUT_LINE_EDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class InputLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    InputLineEdit(QWidget *parent = nullptr) : QLineEdit(parent), _focus(false) {}

public slots:
    void set_focus(bool focus){ _focus = focus; if(_focus) setFocus(); else clearFocus(); };

signals:
    void signal_key_input_edit(QString& text);

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        QString text = event->text();
        emit signal_key_input_edit(text);
    }

    void focusOutEvent(QFocusEvent *) override {
        if(_focus)
            setFocus();
        else
            clearFocus();
    }
private:
    bool _focus;
};

#endif // INPUT_LINE_EDIT_H
