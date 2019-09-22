#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>

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
    QString filtro = "Todos os Arquivos(*.*) ;; Texto (*.txt)";// filtro para mostrar apenas os arquivos txt
    //faz a abertura da cx de dialogo
    QString abrirArquivo = QFileDialog::getOpenFileName(this,"Abrir Arquivos","C://",filtro);
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
