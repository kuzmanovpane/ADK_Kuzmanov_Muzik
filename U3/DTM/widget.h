#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    private:
        int n;
        double zmin, zmax, dz;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clearPoints_clicked();

    void on_pushButton_cleardt_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_pushButton_drawContours_clicked();

    void on_pushButton_drawSlope_clicked();

    void on_pushButton_ClearAll_clicked();

    void on_pushButton_Exposition_clicked();

    void on_pushButton_LoadPoints_clicked();

    void on_pushButton_mcLabels_clicked();

    void on_pushButton_Generate_clicked();

    void on_pushButton_clearContours_clicked();

    void on_pushButton_createDT_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
