#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

namespace Ui {
    class MainWindow;
}

class PolRunTool;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    PolRunTool *mRunner;

private slots:
    void on_listWidget_available_doubleClicked(QModelIndex index);
    void on_actionSettings_triggered();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
