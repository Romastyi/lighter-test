/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *ServerLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *HostLabel;
    QLineEdit *HostEdit;
    QLabel *PortLabel;
    QSpinBox *PortSpin;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(400, 111);
        verticalLayout = new QVBoxLayout(SettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ServerLabel = new QLabel(SettingsDialog);
        ServerLabel->setObjectName(QStringLiteral("ServerLabel"));

        verticalLayout->addWidget(ServerLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        HostLabel = new QLabel(SettingsDialog);
        HostLabel->setObjectName(QStringLiteral("HostLabel"));

        horizontalLayout->addWidget(HostLabel);

        HostEdit = new QLineEdit(SettingsDialog);
        HostEdit->setObjectName(QStringLiteral("HostEdit"));

        horizontalLayout->addWidget(HostEdit);

        PortLabel = new QLabel(SettingsDialog);
        PortLabel->setObjectName(QStringLiteral("PortLabel"));

        horizontalLayout->addWidget(PortLabel);

        PortSpin = new QSpinBox(SettingsDialog);
        PortSpin->setObjectName(QStringLiteral("PortSpin"));
        PortSpin->setMaximum(65535);

        horizontalLayout->addWidget(PortSpin);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Dialog", 0));
        ServerLabel->setText(QApplication::translate("SettingsDialog", "Server address:", 0));
        HostLabel->setText(QApplication::translate("SettingsDialog", "Host:", 0));
        PortLabel->setText(QApplication::translate("SettingsDialog", "Port:", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
