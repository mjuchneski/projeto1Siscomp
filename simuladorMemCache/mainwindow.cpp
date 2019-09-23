#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

QFile arquivo;
QString abrirArquivo;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /*Abertura do arquivo*/
    QString filtro = "Todos os Arquivos(*.*) ;; Texto (*.txt)";// filtro para mostrar apenas os arquivos txt
    //faz a abertura da cx de dialogo
    abrirArquivo = QFileDialog::getOpenFileName(this,"Abrir Arquivos","C:/Users/Higo Alves/Documents/GitHub/projeto1Siscomp/",filtro);

    /*Manipulação do arquivo*/
    QFile arquivo(abrirArquivo);//faz a criação do arquivo
    if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
        QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
    }
    QTextStream entrada(&arquivo);

    QString texto = entrada.readAll();// faz a leitura do arquivo e retorna uma string
    ui->plainTextEdit->setPlainText(texto);// passa o conteudo do texto para o plaintext
    arquivo.close();
}




void MainWindow::on_radioDireto_clicked()
{
    ui->radioFIFO->hide();
    ui->radioLFU->hide();
    ui->radioLRU->hide();
    ui->radioRANDOM->hide();
}

void MainWindow::on_radioAssociativo_clicked()
{
    ui->radioFIFO->show();
    ui->radioLFU->show();
    ui->radioLRU->show();
    ui->radioRANDOM->show();
}

void MainWindow::on_radioAssociativoConjunto_clicked()
{
    ui->radioFIFO->show();
    ui->radioLFU->show();
    ui->radioLRU->show();
    ui->radioRANDOM->show();
}

void MainWindow::on_btnInserir_clicked()
{

        ui->tableCache->setRowCount(ui->editCapacidadeCache->text().toInt());
        ui->tableCache->setColumnCount(2);
        ui->tableCache->verticalHeader()->setVisible(false);
        ui->tableCache->setEditTriggers(QAbstractItemView::NoEditTriggers);

}


void MainWindow::on_btnRodar_clicked()
{
    QString concatena = "";
    int row = 0, col = 0, posicaoDaVirgula = 0;
    QFile arquivo(abrirArquivo);
    if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
        QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
    }
    QTextStream entrada(&arquivo);
    while (!arquivo.atEnd()) {
        QString line = arquivo.readLine();//faz a leitura de uma linha

        for (int c = 0;c < line.length();c++) {
            if (line[c] == ","){
                posicaoDaVirgula = c;
            }
        }

        for (int i = 0; i < posicaoDaVirgula; i++) {
            concatena = concatena + line[i];
            ui->tableCache->setItem(row, 0, new QTableWidgetItem(concatena));
        }
        concatena = "";
        for (int i = posicaoDaVirgula; i < line.length(); i++) {
            concatena = concatena + line[i+1];
            ui->tableCache->setItem(row, 1, new QTableWidgetItem(concatena));
        }
        row++;

        /*if (line[c] != ","){
                a = line[c];
                ui->tableCache->setItem(row, 0, new QTableWidgetItem(a));
            }
            row++;*/
        //qDebug() << line;

    }
    //ui->tableCache->setItem(0, 1, new QTableWidgetItem("#linha 0, coluna 1"));

}
