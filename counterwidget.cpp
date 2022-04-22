
#include <QHBoxLayout>
#include "counterwidget.h"
#include "config.h"

CounterWidget::CounterWidget(QWidget *parent)
    : QWidget(parent), m_count(0), m_timer(this), m_gpio(this), m_Num(0)
{
    setWindowTitle("BinaryCounter");
    resize(300, 200);
    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);

    // QLCDNumber zur Anzeige des Zaehlerstandes dezimal:

    m_Lcd = new QLCDNumber(2);
    layout->addWidget(m_Lcd);
    m_Lcd->display(m_Num);

    connect(&m_timer, &QTimer::timeout, this, &CounterWidget::updateCounter);
    m_timer.start(T_UPDATE);
}

CounterWidget::~CounterWidget()
{

}

void CounterWidget::updateLEDs()
{
    for(int i = 0; i < 4; i++) m_gpio.set(LEDS[i], (m_Num >> i) & 0b1);
}

// Zaehlerstand im Widget und dual ueber LEDs anzeigen:

void CounterWidget::updateCounter()
{
    if(m_gpio.isActivated(BUTTONS[2])) m_Num = (m_Num + 1);
    if(m_gpio.isActivated(BUTTONS[0])) m_Num = (m_Num - 1);
    if(m_gpio.isActivated(BUTTONS[1])) m_Num = 0;
    if(m_Num > 15) m_Num = 0;
    if(m_Num < 0) m_Num = 15;
    m_Lcd->display(m_Num);
    updateLEDs();
}

