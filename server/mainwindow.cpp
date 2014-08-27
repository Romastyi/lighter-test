#include "mainwindow.h"
#include "ui_mainwindow.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
