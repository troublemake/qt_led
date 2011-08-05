#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include "gpio.h"
#include "chestnut.h"

class MyWidget : public QWidget {
public:     MyWidget(QWidget *parent = 0);

private:
    Gpio * _blue_led;
    Gpio * _red_led;

private slots:
    void on_toggle_gpio_led_red_clicked();
    void on_toggle_gpio_led_blue_clicked();
};

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent) {
    //     setFixedSize(200, 120);
    QPushButton *ledButton = new QPushButton(tr("LED an/aus"), this);
    ledButton->setGeometry(62, 40, 140, 30);
    ledButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(ledButton, SIGNAL(clicked()), qApp, SLOT(on_toggle_gpio_led_red_clicked()));

    QPushButton *quitButton = new QPushButton(tr("Quit"), this);
    quitButton->setGeometry(62, 80, 75, 30);
    quitButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MyWidget::on_toggle_gpio_led_blue_clicked()
{
    GpioState state = _blue_led->get_state();
    if (state == GPIO_STATE_LOW) {
        _blue_led->set_state(GPIO_STATE_HIGH);
    } else {
        _blue_led->set_state(GPIO_STATE_LOW);
    }
}

void MyWidget::on_toggle_gpio_led_red_clicked()
{
    GpioState state = _red_led->get_state();
    if (state == GPIO_STATE_LOW) {
        _red_led->set_state(GPIO_STATE_HIGH);
    } else {
        _red_led->set_state(GPIO_STATE_LOW);
    }
}

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MyWidget widget;
    //   widget.show();
    widget.showFullScreen();
    return app.exec();
}
