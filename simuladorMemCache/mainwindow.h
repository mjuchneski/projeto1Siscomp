#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    //void on_radioButton_9_clicked();

    //void on_radioDireto_objectNameChanged(const QString &objectName);

    //void on_radioDireto_clicked(bool checked);

    void on_radioDireto_clicked();

    void on_radioAssociativo_clicked();

    void on_radioAssociativoConjunto_clicked();

    void on_btnInserir_clicked();

    //void on_pushButton_2_clicked();

    void on_btnRodar_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
