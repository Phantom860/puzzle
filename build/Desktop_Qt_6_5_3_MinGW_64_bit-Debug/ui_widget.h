/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *puzzleGrid;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QPushButton *pushButton_1;
    QPushButton *initButton;
    QPushButton *runButton;
    QComboBox *algorithmCombo;
    QLabel *selectLabel;
    QLabel *titleLabel;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *timeLabel;
    QLabel *stepsLabel;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *resultLabel;
    QLabel *goalLabel;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        verticalLayoutWidget = new QWidget(Widget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(40, 170, 341, 316));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        puzzleGrid = new QGridLayout();
        puzzleGrid->setObjectName("puzzleGrid");
        pushButton_8 = new QPushButton(verticalLayoutWidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setMaximumSize(QSize(100, 100));

        puzzleGrid->addWidget(pushButton_8, 2, 1, 1, 1);

        pushButton_9 = new QPushButton(verticalLayoutWidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setMaximumSize(QSize(100, 100));

        puzzleGrid->addWidget(pushButton_9, 2, 2, 1, 1);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(100, 100));
        pushButton_4->setMaximumSize(QSize(100, 100));

        puzzleGrid->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(100, 100));
        pushButton_2->setMaximumSize(QSize(100, 100));

        puzzleGrid->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(100, 100));
        pushButton_5->setMaximumSize(QSize(100, 100));

        puzzleGrid->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMaximumSize(QSize(100, 100));

        puzzleGrid->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_7 = new QPushButton(verticalLayoutWidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setMinimumSize(QSize(100, 100));
        pushButton_7->setMaximumSize(QSize(100, 100));

        puzzleGrid->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMaximumSize(QSize(100, 100));

        puzzleGrid->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton_1 = new QPushButton(verticalLayoutWidget);
        pushButton_1->setObjectName("pushButton_1");
        pushButton_1->setMinimumSize(QSize(100, 100));
        pushButton_1->setMaximumSize(QSize(100, 100));
        pushButton_1->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\230\277\351\207\214\345\246\210\345\246\210\344\270\234\346\226\271\345\244\247\346\245\267\";"));

        puzzleGrid->addWidget(pushButton_1, 0, 0, 1, 1);


        verticalLayout->addLayout(puzzleGrid);

        initButton = new QPushButton(Widget);
        initButton->setObjectName("initButton");
        initButton->setGeometry(QRect(50, 510, 141, 41));
        initButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 188, 140);\n"
"font: 16pt \"Calibri\";"));
        runButton = new QPushButton(Widget);
        runButton->setObjectName("runButton");
        runButton->setGeometry(QRect(230, 510, 141, 41));
        runButton->setStyleSheet(QString::fromUtf8("font: 16pt \"Calibri\";\n"
"background-color: rgb(255, 188, 140);"));
        algorithmCombo = new QComboBox(Widget);
        algorithmCombo->addItem(QString());
        algorithmCombo->addItem(QString());
        algorithmCombo->addItem(QString());
        algorithmCombo->addItem(QString());
        algorithmCombo->setObjectName("algorithmCombo");
        algorithmCombo->setGeometry(QRect(460, 230, 301, 41));
        algorithmCombo->setStyleSheet(QString::fromUtf8("\n"
"font: 12pt \"Calibri\";"));
        selectLabel = new QLabel(Widget);
        selectLabel->setObjectName("selectLabel");
        selectLabel->setGeometry(QRect(460, 180, 321, 20));
        selectLabel->setStyleSheet(QString::fromUtf8("font: 20pt \"\351\230\277\351\207\214\345\246\210\345\246\210\344\270\234\346\226\271\345\244\247\346\245\267\";"));
        titleLabel = new QLabel(Widget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(80, 50, 671, 51));
        titleLabel->setStyleSheet(QString::fromUtf8("font: 36pt \"\351\230\277\351\207\214\345\246\210\345\246\210\344\270\234\346\226\271\345\244\247\346\245\267\";"));
        verticalLayoutWidget_2 = new QWidget(Widget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(460, 430, 221, 91));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        timeLabel = new QLabel(verticalLayoutWidget_2);
        timeLabel->setObjectName("timeLabel");
        timeLabel->setStyleSheet(QString::fromUtf8("font: 16pt \"Calibri\";"));

        verticalLayout_2->addWidget(timeLabel);

        stepsLabel = new QLabel(verticalLayoutWidget_2);
        stepsLabel->setObjectName("stepsLabel");
        stepsLabel->setStyleSheet(QString::fromUtf8("font: 16pt \"Calibri\";"));

        verticalLayout_2->addWidget(stepsLabel);

        verticalLayoutWidget_3 = new QWidget(Widget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(460, 310, 331, 101));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        resultLabel = new QLabel(verticalLayoutWidget_3);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setStyleSheet(QString::fromUtf8("font: 20pt \"\351\230\277\351\207\214\345\246\210\345\246\210\344\270\234\346\226\271\345\244\247\346\245\267\";"));

        verticalLayout_4->addWidget(resultLabel);

        goalLabel = new QLabel(verticalLayoutWidget_3);
        goalLabel->setObjectName("goalLabel");
        goalLabel->setStyleSheet(QString::fromUtf8("font: 16pt \"Calibri\";"));

        verticalLayout_4->addWidget(goalLabel);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_1->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        initButton->setText(QCoreApplication::translate("Widget", "Initialization", nullptr));
        runButton->setText(QCoreApplication::translate("Widget", "Run", nullptr));
        algorithmCombo->setItemText(0, QCoreApplication::translate("Widget", "BFS (Breadth-First-Search)", nullptr));
        algorithmCombo->setItemText(1, QCoreApplication::translate("Widget", "DFS (Depth-First-Search)", nullptr));
        algorithmCombo->setItemText(2, QCoreApplication::translate("Widget", "BFS (Best-First-Search)", nullptr));
        algorithmCombo->setItemText(3, QCoreApplication::translate("Widget", "Branch-And-Bound", nullptr));

        selectLabel->setText(QCoreApplication::translate("Widget", "Please select one of them:", nullptr));
        titleLabel->setText(QCoreApplication::translate("Widget", "Solution for 8 - Puzzle problem", nullptr));
        timeLabel->setText(QCoreApplication::translate("Widget", "Time(s): 0", nullptr));
        stepsLabel->setText(QCoreApplication::translate("Widget", "Steps: 0", nullptr));
        resultLabel->setText(QCoreApplication::translate("Widget", "Result:", nullptr));
        goalLabel->setText(QCoreApplication::translate("Widget", "(No) Goal node", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
