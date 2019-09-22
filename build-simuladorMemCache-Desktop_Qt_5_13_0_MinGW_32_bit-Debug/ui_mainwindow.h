/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioFIFO;
    QRadioButton *radioLFU;
    QRadioButton *radioLRU;
    QRadioButton *radioRANDOM;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioDireto;
    QRadioButton *radioAssociativo;
    QRadioButton *radioAssociativoConjunto;
    QLabel *label_4;
    QLabel *label_5;
    QPlainTextEdit *plainTextEdit;
    QTableWidget *tableCache;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *editCapacidadeCache;
    QPushButton *btnInserir;
    QLineEdit *lineEdit_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(691, 565);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 10, 551, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 60, 101, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(520, 60, 81, 16));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(230, 180, 120, 131));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 84, 88));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioFIFO = new QRadioButton(layoutWidget);
        radioFIFO->setObjectName(QString::fromUtf8("radioFIFO"));
        radioFIFO->setChecked(false);

        verticalLayout->addWidget(radioFIFO);

        radioLFU = new QRadioButton(layoutWidget);
        radioLFU->setObjectName(QString::fromUtf8("radioLFU"));

        verticalLayout->addWidget(radioLFU);

        radioLRU = new QRadioButton(layoutWidget);
        radioLRU->setObjectName(QString::fromUtf8("radioLRU"));

        verticalLayout->addWidget(radioLRU);

        radioRANDOM = new QRadioButton(layoutWidget);
        radioRANDOM->setObjectName(QString::fromUtf8("radioRANDOM"));

        verticalLayout->addWidget(radioRANDOM);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 430, 131, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 430, 75, 23));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(230, 320, 171, 101));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 143, 65));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        radioDireto = new QRadioButton(layoutWidget1);
        radioDireto->setObjectName(QString::fromUtf8("radioDireto"));

        verticalLayout_3->addWidget(radioDireto);

        radioAssociativo = new QRadioButton(layoutWidget1);
        radioAssociativo->setObjectName(QString::fromUtf8("radioAssociativo"));

        verticalLayout_3->addWidget(radioAssociativo);

        radioAssociativoConjunto = new QRadioButton(layoutWidget1);
        radioAssociativoConjunto->setObjectName(QString::fromUtf8("radioAssociativoConjunto"));

        verticalLayout_3->addWidget(radioAssociativoConjunto);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(230, 80, 151, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(440, 470, 91, 20));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 90, 211, 331));
        tableCache = new QTableWidget(centralWidget);
        if (tableCache->columnCount() < 2)
            tableCache->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableCache->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableCache->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableCache->setObjectName(QString::fromUtf8("tableCache"));
        tableCache->setGeometry(QRect(465, 90, 221, 331));
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(230, 110, 186, 60));
        verticalLayout_4 = new QVBoxLayout(layoutWidget2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        editCapacidadeCache = new QLineEdit(layoutWidget2);
        editCapacidadeCache->setObjectName(QString::fromUtf8("editCapacidadeCache"));
        QFont font;
        font.setPointSize(14);
        editCapacidadeCache->setFont(font);

        verticalLayout_4->addWidget(editCapacidadeCache);

        btnInserir = new QPushButton(layoutWidget2);
        btnInserir->setObjectName(QString::fromUtf8("btnInserir"));

        verticalLayout_4->addWidget(btnInserir);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(540, 460, 113, 31));
        lineEdit_2->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 691, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><h3 style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:6pt; font-weight:600;\">Projeto 1 - Simulador de algoritmos de substitui\303\247\303\243o de p\303\241gina de mem\303\263ria em cache</span></h3></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Arquivo de Entrada", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Mem\303\263ria Cache", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Algoritmo", nullptr));
        radioFIFO->setText(QCoreApplication::translate("MainWindow", "FIFO", nullptr));
        radioLFU->setText(QCoreApplication::translate("MainWindow", "LFU", nullptr));
        radioLRU->setText(QCoreApplication::translate("MainWindow", "LRU", nullptr));
        radioRANDOM->setText(QCoreApplication::translate("MainWindow", "RANDOM", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Carregar Instru\303\247\303\265es", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Rodar", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Mapeamento", nullptr));
        radioDireto->setText(QCoreApplication::translate("MainWindow", "Direto", nullptr));
        radioAssociativo->setText(QCoreApplication::translate("MainWindow", "Associativo", nullptr));
        radioAssociativoConjunto->setText(QCoreApplication::translate("MainWindow", "Associativo por conjunto", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Capacidade total da  cache ", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Fra\303\247\303\243o de acertos", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableCache->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Endere\303\247o", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableCache->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Dado", nullptr));
        btnInserir->setText(QCoreApplication::translate("MainWindow", "Inserir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
