#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->HostEdit->setText("127.0.0.1");
    ui->PortSpin->setValue(9999);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::host() const
{
    return ui->HostEdit->text();
}

quint16 SettingsDialog::port() const
{
    return ui->PortSpin->value();
}
