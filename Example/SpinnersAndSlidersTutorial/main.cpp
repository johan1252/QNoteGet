#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[])
{
    //create the main window
    QApplication a(argc, argv);
    QWidget *mainWindow = new QWidget;
    mainWindow->setWindowTitle("How many chicken wings?");

    //create the widgets
    QSpinBox *spinner = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);
    spinner->setRange(1, 50);
    slider->setRange(1, 50);

    //connect the widgets to each other
    //parameters: (object changed by user, change event, object to apply changes to, how to change)
    QObject::connect(spinner, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinner, SLOT(setValue(int)));
    spinner->setValue(10);

    //instantiate layout
    QHBoxLayout *layout = new QHBoxLayout;
    //push widgets onto layout
    layout->addWidget(slider);
    layout->addWidget(spinner);

    //add layout to window
    mainWindow->setLayout(layout);
    //show window
    mainWindow->show();

    return a.exec();
}
