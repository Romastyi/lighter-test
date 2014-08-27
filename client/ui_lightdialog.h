/********************************************************************************
** Form generated from reading UI file 'lightdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTDIALOG_H
#define UI_LIGHTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LightDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lighter;

    void setupUi(QDialog *LightDialog)
    {
        if (LightDialog->objectName().isEmpty())
            LightDialog->setObjectName(QStringLiteral("LightDialog"));
        LightDialog->resize(200, 200);
        verticalLayout = new QVBoxLayout(LightDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Lighter = new QLabel(LightDialog);
        Lighter->setObjectName(QStringLiteral("Lighter"));
        Lighter->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lighter);


        retranslateUi(LightDialog);

        QMetaObject::connectSlotsByName(LightDialog);
    } // setupUi

    void retranslateUi(QDialog *LightDialog)
    {
        LightDialog->setWindowTitle(QApplication::translate("LightDialog", "Dialog", 0));
        Lighter->setText(QApplication::translate("LightDialog", "OFF", 0));
    } // retranslateUi

};

namespace Ui {
    class LightDialog: public Ui_LightDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHTDIALOG_H
