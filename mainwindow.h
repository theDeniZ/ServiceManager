#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <servicehistory.h>
#include <servicemanager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ServiceManager manager = ServiceManager();
    ServiceHistory * service;
    QString fileName;
    int selectedRow = -1;
    int selectedService = -1;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionCreate_triggered();

    void on_actionOpen_Test_triggered();

    void on_actionSafe_triggered();

    void on_actionSave_as_triggered();

    void on_servicesTable_cellClicked(int row, int column);

    void on_historyCheckBox_stateChanged();

    void on_time_userDateChanged(const QDate &date);

    void on_milage_textChanged(const QString &arg1);

    void on_dealer_textChanged(const QString &arg1);

    void on_bmw_stateChanged(int arg1);

    void on_status_currentIndexChanged(int index);

    void on_addTopHistory_clicked();

    void on_deleteSelectedHistory_clicked();

    void on_serviceItemsTable_cellClicked(int row, int column);

    void on_addBottomHistory_clicked();

    void on_serviceType_currentIndexChanged(int index);

    void on_serviceStatus_currentIndexChanged(int index);

    void on_deleteSelectedService_clicked();

    void on_addTopService_clicked();

    void on_addBottomService_clicked();

private:
    Ui::MainWindow *ui;
    void reloadTable();
    void reloadSecondTable();
    void setFirstSelectionAvailable(bool);
    void setSecondSelectionAvailable(bool);
};
#endif // MAINWINDOW_H
