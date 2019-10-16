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
    QPushButton *btnRodar;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioDireto;
    QRadioButton *radioAssociativo;
    QRadioButton *radioAssociativoConjunto;
    QLabel *label_5;
    QPlainTextEdit *plainTextEdit;
    QTableWidget *tableCache;
    QLineEdit *editHit;
    QLineEdit *editMiss;
    QLabel *label_6;
    QLineEdit *editCapacidadeCache;
    QLabel *label_4;
    QLabel *label_7;
    QPushButton *btnInserir;
    QLineEdit *editConjuntos;
    QLabel *label_8;
    QLineEdit *editFracaoAcertos;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(963, 656);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 10, 601, 31));
        QFont font;
        font.setPointSize(9);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 60, 121, 16));
        QFont font1;
        font1.setPointSize(10);
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(520, 60, 101, 16));
        label_3->setFont(font1);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(230, 210, 120, 131));
        groupBox->setFont(font1);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 84, 100));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioFIFO = new QRadioButton(layoutWidget);
        radioFIFO->setObjectName(QString::fromUtf8("radioFIFO"));
        radioFIFO->setFont(font1);
        radioFIFO->setChecked(false);

        verticalLayout->addWidget(radioFIFO);

        radioLFU = new QRadioButton(layoutWidget);
        radioLFU->setObjectName(QString::fromUtf8("radioLFU"));
        radioLFU->setFont(font1);

        verticalLayout->addWidget(radioLFU);

        radioLRU = new QRadioButton(layoutWidget);
        radioLRU->setObjectName(QString::fromUtf8("radioLRU"));
        radioLRU->setFont(font1);

        verticalLayout->addWidget(radioLRU);

        radioRANDOM = new QRadioButton(layoutWidget);
        radioRANDOM->setObjectName(QString::fromUtf8("radioRANDOM"));
        radioRANDOM->setFont(font1);

        verticalLayout->addWidget(radioRANDOM);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 430, 131, 31));
        pushButton->setFont(font1);
        btnRodar = new QPushButton(centralWidget);
        btnRodar->setObjectName(QString::fromUtf8("btnRodar"));
        btnRodar->setGeometry(QRect(270, 480, 75, 31));
        btnRodar->setFont(font1);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(220, 340, 191, 101));
        groupBox_2->setFont(font1);
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 164, 74));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        radioDireto = new QRadioButton(layoutWidget1);
        radioDireto->setObjectName(QString::fromUtf8("radioDireto"));
        radioDireto->setFont(font1);

        verticalLayout_3->addWidget(radioDireto);

        radioAssociativo = new QRadioButton(layoutWidget1);
        radioAssociativo->setObjectName(QString::fromUtf8("radioAssociativo"));
        radioAssociativo->setFont(font1);

        verticalLayout_3->addWidget(radioAssociativo);

        radioAssociativoConjunto = new QRadioButton(layoutWidget1);
        radioAssociativoConjunto->setObjectName(QString::fromUtf8("radioAssociativoConjunto"));
        radioAssociativoConjunto->setFont(font1);

        verticalLayout_3->addWidget(radioAssociativoConjunto);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(410, 470, 111, 20));
        label_5->setFont(font1);
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 90, 211, 331));
        plainTextEdit->setFont(font1);
        tableCache = new QTableWidget(centralWidget);
        if (tableCache->columnCount() < 3)
            tableCache->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableCache->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableCache->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableCache->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableCache->setObjectName(QString::fromUtf8("tableCache"));
        tableCache->setGeometry(QRect(432, 91, 351, 350));
        tableCache->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font2.setPointSize(10);
        tableCache->setFont(font2);
        tableCache->setLineWidth(1);
        tableCache->setColumnCount(3);
        tableCache->horizontalHeader()->setMinimumSectionSize(40);
        tableCache->horizontalHeader()->setDefaultSectionSize(116);
        tableCache->verticalHeader()->setDefaultSectionSize(25);
        editHit = new QLineEdit(centralWidget);
        editHit->setObjectName(QString::fromUtf8("editHit"));
        editHit->setGeometry(QRect(540, 460, 113, 31));
        QFont font3;
        font3.setPointSize(14);
        editHit->setFont(font3);
        editHit->setStyleSheet(QString::fromUtf8("color: rgb(70, 211, 0);"));
        editMiss = new QLineEdit(centralWidget);
        editMiss->setObjectName(QString::fromUtf8("editMiss"));
        editMiss->setGeometry(QRect(540, 500, 113, 31));
        editMiss->setFont(font3);
        editMiss->setStyleSheet(QString::fromUtf8("color: rgb(226, 0, 0);"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(410, 510, 101, 16));
        label_6->setFont(font1);
        editCapacidadeCache = new QLineEdit(centralWidget);
        editCapacidadeCache->setObjectName(QString::fromUtf8("editCapacidadeCache"));
        editCapacidadeCache->setGeometry(QRect(230, 80, 184, 29));
        editCapacidadeCache->setFont(font3);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(230, 40, 184, 54));
        label_4->setFont(font1);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(230, 110, 184, 16));
        label_7->setFont(font1);
        btnInserir = new QPushButton(centralWidget);
        btnInserir->setObjectName(QString::fromUtf8("btnInserir"));
        btnInserir->setGeometry(QRect(230, 170, 184, 31));
        btnInserir->setFont(font1);
        editConjuntos = new QLineEdit(centralWidget);
        editConjuntos->setObjectName(QString::fromUtf8("editConjuntos"));
        editConjuntos->setGeometry(QRect(230, 130, 184, 31));
        editConjuntos->setFont(font3);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(410, 560, 111, 20));
        label_8->setFont(font1);
        editFracaoAcertos = new QLineEdit(centralWidget);
        editFracaoAcertos->setObjectName(QString::fromUtf8("editFracaoAcertos"));
        editFracaoAcertos->setGeometry(QRect(540, 550, 113, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 963, 21));
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
        btnRodar->setText(QCoreApplication::translate("MainWindow", "Rodar", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Mapeamento", nullptr));
        radioDireto->setText(QCoreApplication::translate("MainWindow", "Direto", nullptr));
        radioAssociativo->setText(QCoreApplication::translate("MainWindow", "Associativo", nullptr));
        radioAssociativoConjunto->setText(QCoreApplication::translate("MainWindow", "Associativo por conjunto", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Hits", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableCache->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Validade", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableCache->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Endere\303\247o", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableCache->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Dado", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Misses", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Capacidade total da  cache ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Quantidade de Conjuntos", nullptr));
        btnInserir->setText(QCoreApplication::translate("MainWindow", "Inserir", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Fra\303\247\303\243o de acertos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
