#ifndef VIEWCLASSES_H
#define VIEWCLASSES_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class ViewClasses;
}

class ViewClasses : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewClasses(QWidget *parent = 0);
    ~ViewClasses();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_pushButton_addClasses_clicked();

private:
    Ui::ViewClasses *ui;
};

#endif // VIEWCLASSES_H
