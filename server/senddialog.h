#ifndef SENDDIALOG_H
#define SENDDIALOG_H

#include <QDialog>
#include "server.h"

namespace Ui {
class SendDialog;
}

class SendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendDialog(QWidget *parent = 0);
    ~SendDialog();

    bool isStarted() const;

protected:
    void sendCommand(char command, const QByteArray &value = QByteArray());

private slots:
    void connectionsChanged();
    void on_OnButton_clicked();
    void on_OffButton_clicked();
    void on_ColorButton_clicked();
    void on_CloseAllButton_clicked();
    
private:
    Ui::SendDialog *ui;
    Server *server;
};

#endif // SENDDIALOG_H
