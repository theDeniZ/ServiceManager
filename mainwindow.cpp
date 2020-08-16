#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->service = new ServiceHistory();

    ui->setupUi(this);

    this->setWindowTitle("BMW Service History Manager");
    ui->servicesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->servicesTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->serviceItemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->serviceItemsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->status->addItems(ServiceTimeList());
    ui->serviceStatus->addItems(ServiceTimeList());
    ui->serviceType->addItems(ServiceItemsList());
    ui->milage->setValidator(new QIntValidator(0, 999999, this));

    setFirstSelectionAvailable(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionCreate_triggered() {
    this->fileName = QFileDialog::getSaveFileName(this, tr("Create File"), QDir::homePath() + "/Desktop/test.tst", tr("Test file (*.tst)"));
    if (this->fileName.count()) {
        this->service = new ServiceHistory();
        if (!this->manager.writeHistoryToFile(fileName, this->service)) {
            QMessageBox::information(0, "error", "Could not create file");
        }
        reloadTable();
    }
}

void MainWindow::on_actionOpen_Test_triggered() {
    this->fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath() + "/Desktop", tr("Test file (*.tst)"));
    if (this->fileName.count()) {
        this->service = this->manager.readHistoryFromFile(fileName);
        if (!this->service) {
            QMessageBox::information(0, "error", "Could not open file");
        }
        reloadTable();
    }
}

void MainWindow::on_actionSafe_triggered() {
    if (this->fileName.count() > 0) {
        if (!this->manager.writeHistoryToFile(this->fileName, this->service)) {
            QMessageBox::information(0, "error", "Could not save file");
        }
    } else {
        on_actionSave_as_triggered();
    }
}

void MainWindow::on_actionSave_as_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Create File"), QDir::homePath() + "/Desktop/test.tst", tr("Test file (*.tst)"));
    if (fileName.count()) {
        if (!this->manager.writeHistoryToFile(fileName, this->service)) {
            QMessageBox::information(0, "error", "Could not save file");
        }
        if (this->fileName.count() == 0) {
            this->fileName = fileName;
        }
    }
}

void MainWindow::reloadTable() {
    ui->historyCheckBox->setChecked(this->manager.eraseHistory);
    ui->servicesTable->setColumnCount(5);
    ui->servicesTable->setHorizontalHeaderLabels(QStringList() << "Date" << "Milage" << "Dealer" << "BMW" << "Status");
    ui->servicesTable->setRowCount(this->service->services.count());
    for (int i = 0; i < this->service->services.count(); ++i) {
        ui->servicesTable->setItem(i, 0, new QTableWidgetItem(this->service->services[i].date.toString("dd.MM.yyyy")));
        ui->servicesTable->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(this->service->services[i].milage)));
        ui->servicesTable->setItem(i, 2, new QTableWidgetItem(this->service->services[i].dealer));
        ui->servicesTable->setItem(i, 3, new QTableWidgetItem(this->service->services[i].bmw ? "yes" : "no"));
        ui->servicesTable->setItem(i, 4, new QTableWidgetItem(TimeStringValue(this->service->services[i].time)));
    }
}

void MainWindow::reloadSecondTable() {
    ui->serviceItemsTable->setColumnCount(2);
    ui->serviceItemsTable->setHorizontalHeaderLabels(QStringList() << "Type" << "Status");
    ui->serviceItemsTable->setRowCount(this->service->services[this->selectedRow].items.count());
    for (int i = 0; i < this->service->services[this->selectedRow].items.count(); ++i) {
        ServiceItem item = this->service->services[this->selectedRow].items[i];
        ui->serviceItemsTable->setItem(i, 0, new QTableWidgetItem(ServiceStringValue(item.type)));
        ui->serviceItemsTable->setItem(i, 1, new QTableWidgetItem(TimeStringValue(item.time)));
    }
}

void MainWindow::setFirstSelectionAvailable(bool available) {
    ui->time->setEnabled(available);
    ui->milage->setEnabled(available);
    ui->dealer->setEnabled(available);
    ui->bmw->setEnabled(available);
    ui->status->setEnabled(available);
    ui->deleteSelectedHistory->setEnabled(available);

    ui->serviceItemsTable->setEnabled(available);
    ui->addTopService->setEnabled(available);
    ui->addBottomService->setEnabled(available);

    if (!available) {
        setSecondSelectionAvailable(false);
    }
}

void MainWindow::setSecondSelectionAvailable(bool available) {
    ui->deleteSelectedService->setEnabled(available);
    ui->serviceStatus->setEnabled(available);
    ui->serviceType->setEnabled(available);
}

void MainWindow::on_servicesTable_cellClicked(int row, int column) {
    this->selectedRow = row;
    Service s = this->service->services[row];
    setFirstSelectionAvailable(true);

    ui->time->setDate(s.date);
    ui->milage->setText(tr("%1").arg(s.milage));
    ui->dealer->setText(s.dealer);
    ui->bmw->setChecked(s.bmw);
    ui->status->setCurrentIndex(IndexForTime(s.time));

    reloadSecondTable();
    setSecondSelectionAvailable(false);
}

void MainWindow::on_historyCheckBox_stateChanged() {
    this->manager.eraseHistory = ui->historyCheckBox->checkState();
}

void MainWindow::on_time_userDateChanged(const QDate &date) {
    int i = this->selectedRow;
    this->service->services[i].date = date;
    ui->servicesTable->setItem(i, 0, new QTableWidgetItem(this->service->services[i].date.toString("dd.MM.yyyy")));
}

void MainWindow::on_milage_textChanged(const QString &arg1) {
    int i = this->selectedRow;
    this->service->services[i].milage = arg1.toInt();
    ui->servicesTable->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(this->service->services[i].milage)));
}

void MainWindow::on_dealer_textChanged(const QString &arg1) {
    int i = this->selectedRow;
    this->service->services[i].dealer = arg1;
    ui->servicesTable->setItem(i, 2, new QTableWidgetItem(this->service->services[i].dealer));
}

void MainWindow::on_bmw_stateChanged(int arg1) {
    int i = this->selectedRow;
    this->service->services[i].bmw = ui->bmw->isChecked();
    ui->servicesTable->setItem(i, 3, new QTableWidgetItem(this->service->services[i].bmw ? "yes" : "no"));
}

void MainWindow::on_status_currentIndexChanged(int index) {
    if (this->selectedRow < 0) { return; }
    int i = this->selectedRow;
    this->service->services[i].time = index == 1 ? late : index == 2 ? over : ok;
    ui->servicesTable->setItem(i, 4, new QTableWidgetItem(TimeStringValue(this->service->services[i].time)));
}

void MainWindow::on_addTopHistory_clicked() {
    this->service->services.insert(0, Service());
    setFirstSelectionAvailable(false);
    this->selectedRow = -1;
    reloadTable();
}

void MainWindow::on_deleteSelectedHistory_clicked() {
    this->service->services.removeAt(this->selectedRow);
    this->selectedRow = -1;
    setFirstSelectionAvailable(false);
    reloadTable();
}

void MainWindow::on_addBottomHistory_clicked() {
    this->service->services.append(Service());
    reloadTable();
}

void MainWindow::on_serviceItemsTable_cellClicked(int row, int column) {
    this->selectedService = row;
    ServiceItem item = this->service->services[this->selectedRow].items[row];
    setSecondSelectionAvailable(true);

    ui->serviceType->setCurrentIndex(IndexForService(item.type));
    ui->serviceStatus->setCurrentIndex(IndexForTime(item.time));
}

void MainWindow::on_serviceType_currentIndexChanged(int index) {
    if (this->selectedRow < 0 || this->selectedService < 0) { return; }
    ServiceItemType type = ServiceForIndex(index);
    this->service->services[this->selectedRow].items[this->selectedService].type = type;
    ui->serviceItemsTable->setItem(this->selectedService, 0, new QTableWidgetItem(ServiceStringValue(type)));
}

void MainWindow::on_serviceStatus_currentIndexChanged(int index) {
    if (this->selectedRow < 0 || this->selectedService < 0) { return; }
    this->service->services[this->selectedRow].items[this->selectedService].time = index == 1 ? late : index == 2 ? over : ok;
    ui->serviceItemsTable->setItem(this->selectedService, 1, new QTableWidgetItem(TimeStringValue(index == 1 ? late : index == 2 ? over : ok)));
}

void MainWindow::on_deleteSelectedService_clicked() {
    if (this->selectedRow < 0 || this->selectedService < 0) { return; }
    this->service->services[this->selectedRow].items.removeAt(this->selectedService);
    this->selectedService = -1;
    setSecondSelectionAvailable(false);
    reloadSecondTable();
}

void MainWindow::on_addTopService_clicked() {
    this->service->services[this->selectedRow].items.insert(0, ServiceItem(engineOil, ok));
    setSecondSelectionAvailable(false);
    this->selectedService = -1;
    reloadSecondTable();
}

void MainWindow::on_addBottomService_clicked() {
    this->service->services[this->selectedRow].items.append(ServiceItem(engineOil, ok));
    reloadSecondTable();
}
