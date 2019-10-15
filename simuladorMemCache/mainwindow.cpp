#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QRandomGenerator>

QFile arquivo;
QString abrirArquivo;
int fifo = 0;
QVector<int> vet;
//QVector<int> vetLRU;



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
    ui->editConjuntos->hide();
    ui->radioFIFO->hide();
    ui->radioLFU->hide();
    ui->radioLRU->hide();
    ui->radioRANDOM->hide();
}

void MainWindow::on_radioAssociativo_clicked()
{
    ui->editConjuntos->hide();
    ui->radioFIFO->show();
    ui->radioLFU->show();
    ui->radioLRU->show();
    ui->radioRANDOM->show();
}

void MainWindow::on_radioAssociativoConjunto_clicked()
{
    ui->editConjuntos->show();
    ui->radioFIFO->show();
    ui->radioLFU->show();
    ui->radioLRU->show();
    ui->radioRANDOM->show();
}





void MainWindow::on_btnInserir_clicked()
{
    ui->tableCache->setRowCount(ui->editCapacidadeCache->text().toInt());
    ui->tableCache->setColumnCount(3);
    ui->tableCache->verticalHeader()->setVisible(false);
    ui->tableCache->setEditTriggers(QAbstractItemView::NoEditTriggers);
    fifo = 0;

        for (int i = 0 ; i < ui->editCapacidadeCache->text().toInt(); i++) {
            ui->tableCache->setItem(i,0,new QTableWidgetItem("0"));//preenche a linha validade na tabela da cache
            ui->tableCache->setItem(i,1,new QTableWidgetItem(""));
        }//end for
}


void MainWindow::on_btnRodar_clicked()
{

    int hit = 0, miss = 0;
    ui->editMiss->setText(QString::number(miss));
    ui->editHit->setText(QString::number(hit));
//------------Mapeamento Direto-----------------
    if(ui->radioDireto->isChecked() == true){
        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if
        QTextStream entrada(&arquivo);
        while (!arquivo.atEnd()) {
            QString line = arquivo.readLine();//faz a leitura de uma linha
            int tam = ui->editCapacidadeCache->text().toInt();
            int row = line.toInt() % tam;
            if(ui->tableCache->item(row,0)->text() == "0"){// verifica se a validade é 0
                ui->tableCache->setItem(row,1, new QTableWidgetItem(line));
                ui->tableCache->setItem(row,0, new QTableWidgetItem("1"));
                qDebug() << "miss";
                miss ++;
                ui->editMiss->setText(QString::number(miss));
                } else if (ui->tableCache->item(row,0)->text() == "1" && ui->tableCache->item(row,1)->text() == line) {
                            hit ++;
                            qDebug() << "hit";
                            ui->editHit->setText(QString::number(hit));
                        } else if (ui->tableCache->item(row,0)->text() == "1" && ui->tableCache->item(row,1)->text() != line) {
                                    ui->tableCache->setItem(row,1, new QTableWidgetItem(line));
                                    ui->tableCache->setItem(row,0, new QTableWidgetItem("1"));
                                    qDebug() << "miss";
                                    miss ++;
                                    ui->editMiss->setText(QString::number(miss));
                                }
        }   //end while
            arquivo.close();
    }//end if

//----------------Mapeamento Associativo + algoritmo RANDOM--------------------
    if (ui->radioAssociativo->isChecked() && ui->radioRANDOM->isChecked()){
        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if

        QTextStream entrada(&arquivo);
        while (!arquivo.atEnd()) {
            QString line = arquivo.readLine();//faz a leitura de uma linha

            for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
                // ----------verifica se ja existe na cache----------
                if (ui->tableCache->item(i,0)->text()== "1" && ui->tableCache->item(i,1)->text() == line) {
                    hit ++;
                    ui->editHit->setText(QString::number(hit));
                    i = ui->editCapacidadeCache->text().toInt();
                }else if(ui->tableCache->item(i,0)->text() == "0"){
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(line));
                    i = ui->editCapacidadeCache->text().toInt();
                } else if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() != line && i == ui->editCapacidadeCache->text().toInt()-1){
                    int tamanhoRandom = ui->editCapacidadeCache->text().toInt();
                    int random = QRandomGenerator::global()->bounded(tamanhoRandom);
                    ui->tableCache->setItem(random,1, new QTableWidgetItem(line));
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                }
            }//end for
        }//end while
        arquivo.close();
    }//end if


        //----------------Mapeamento Associativo + FIFO--------------------
    if (ui->radioAssociativo->isChecked() && ui->radioFIFO->isChecked()){
        fifo ++;
        bool estado = true;



        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if
        QTextStream entrada(&arquivo);
        vet.resize(ui->editCapacidadeCache->text().toInt());
        if (fifo -1 == 0){
            for (int i = 0; i < vet.size(); i++){
                vet[i]= ui->tableCache->item(i,1)->text().toInt();
            }
        }

        //qDebug()<< vet << "vetor preenchido com o que estava na cache";
        while (!arquivo.atEnd()) {
        QString line = arquivo.readLine();//faz a leitura de uma linha


        for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
            qDebug()<< "entrou no laço 1 ";
            int linhaAtual = line.toInt();
            int linhaCache = ui->tableCache->item(i,1)->text().toInt();

            if (i <= ui->editCapacidadeCache->text().toInt()-1){
                if (estado){
                    if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                        qDebug()<< "verificou se esta vazio, cache vazia";
                        miss ++;
                        ui->editMiss->setText(QString::number(miss));
                        ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                        ui->tableCache->setItem(i,1, new QTableWidgetItem(QString::number(linhaAtual)));
                        vet[i] = linhaAtual;
                        qDebug()<< vet << "miss cache vazia, insere "<< linhaAtual << "no final";
                        break;//i = ui->editCapacidadeCache->text().toInt();
                    }//end if linha vazia
                    else if (ui->tableCache->item(i,0)->text() == "1" && linhaCache == linhaAtual) {//verifica se é hit
                             qDebug()<< "Verificou se é hit cache vazia";
                             hit ++;
                             ui->editHit->setText(QString::number(hit));
                             qDebug()<< vet << "hit, cache vazia "<< linhaAtual << "";
                             break;//i = ui->editCapacidadeCache->text().toInt();
                    }//end if hit cache vazia

                }//end if estado
                if (i >= ui->editCapacidadeCache->text().toInt()-1) {
                        estado = false;
                }
            }//if chegou no final

            if (i == ui->editCapacidadeCache->text().toInt()-1){
                if (!estado){
                qDebug()<<"Estado da cache = "<< estado;

                for (int j = 0;j <= ui->editCapacidadeCache->text().toInt(); j++) {
                    bool verificador = false;

                    int valorAtual = line.toInt();
                    int valorCache = 0;
                    for(int m = 0; m <= ui->editCapacidadeCache->text().toInt() -1; m++){
                        //qDebug()<< m;
                        valorCache = ui->tableCache->item(m,1)->text().toInt();
                        if ( valorAtual == valorCache){
                            verificador = true;
                            qDebug() << "é igual?"<< verificador;
                            break;
                        }//if encontra hit
                    }//for encontra hit

                    if (valorCache == valorAtual && verificador == true){// verifica hit na cache cheia
                        hit ++;
                        ui->editHit->setText(QString::number(hit));
                        qDebug()<< vet<< "hit cache cheia"<< linhaAtual << "";
                        break;
                    }//end if hit cheio
                    else if (valorCache != valorAtual  && verificador == false) {//miss cache cheia
                        miss ++;
                        ui->editMiss->setText(QString::number(miss));

                        int indiceReal = 0;
                        while (indiceReal < ui->editCapacidadeCache->text().toInt()) {
                            if (ui->tableCache->item(indiceReal,1)->text().toInt() == vet[0]){
                                break;
                            }
                            indiceReal+=1;
                        }

                        ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(QString::number(linhaAtual)));

                        vet.pop_front();//remove da cabeça
                        vet.push_back(linhaAtual);//insere na cauda
                        qDebug()<< vet<< "miss cache cheia, insere "<< linhaAtual << "no final";
                        break;
                    }// if miss cheio
                }//for cache cheia
              }//if estado cheio
          }//if for cache cheio





        }//for cache vazia

    }// end while
    arquivo.close();

}
            //---------------------ASSOCIATIVO + LRU-------------------

    if (ui->radioAssociativo->isChecked() && ui->radioLRU->isChecked()){
       QVector<int> vetLRU;
       bool estado = true;

       vetLRU.resize(ui->editCapacidadeCache->text().toInt());
       qDebug()<< vetLRU;
       QFile arquivo(abrirArquivo);
       if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
           QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
       }//end if
       QTextStream entrada(&arquivo);

       while (!arquivo.atEnd()) {
       QString line = arquivo.readLine();//faz a leitura de uma linha
        //qDebug()<< "leu linha";
       for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
           //qDebug()<< "entrou no laço 1 ";
           int linhaAtual = line.toInt();
           int linhaCache = ui->tableCache->item(i,1)->text().toInt();

           if (i <= ui->editCapacidadeCache->text().toInt()-1){
               if (estado){
                   if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                    //qDebug()<< "verificou se esta vazio, cache vazia";
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(QString::number(linhaAtual)));

                    vetLRU.pop_front();//remove da cabeça
                    vetLRU.push_back(linhaAtual);//insere na cauda

                    /*for(int j = 0; j < ui->editCapacidadeCache->text().toInt(); j++){
                        qDebug()<< "reordenou cache vazia";
                        if(j < ui->editCapacidadeCache->text().toInt()-1){
                            vetLRU[j] = vetLRU[j+1];
                        }
                    }
                    vetLRU[ui->editCapacidadeCache->text().toInt()-1] = linhaAtual;*/
                    qDebug()<< vetLRU<< "miss cache vazia, insere "<< linhaAtual << "no final";
                    break;//i = ui->editCapacidadeCache->text().toInt();

                   }//end if linha vazia
                   if (ui->tableCache->item(i,0)->text() == "1" && linhaCache == linhaAtual) {//verifica se é hit
                            //qDebug()<< "Verificou se é hit cache vazia";
                            hit ++;
                            ui->editHit->setText(QString::number(hit));

                            int indiceVetor = 0;
                            for(int m = 0; m <= ui->editCapacidadeCache->text().toInt() -1; m++){
                                //qDebug()<< m;

                                if ( vetLRU[m] == linhaAtual){
                                    indiceVetor++;
                                    break;
                                }
                            }


                            int indiceReal = 0;
                            while (indiceReal < ui->editCapacidadeCache->text().toInt()) {
                                if (ui->tableCache->item(indiceReal,1)->text().toInt() == vetLRU[0]){

                                    break;
                                }
                                indiceReal+=1;
                            }

                            ui->tableCache->setItem(i,1, new QTableWidgetItem(QString::number(linhaAtual)));
                            //vetLRU.move(i,ui->editCapacidadeCache->text().toInt()-1);
                            //qDebug()<< vetLRU[i] << "hit cache vazia, valor a ser movido pro final";
                            vetLRU.push_back(linhaAtual);
                            vetLRU.removeAt(indiceVetor);
                            //vetLRU.pop_front();//remove da cabeça
                            //vetLRU.remove(i);
                            //vetLRU.push_back(linhaAtual);//insere na cauda




                            /*for(int j = 0; j < ui->editCapacidadeCache->text().toInt(); j++){
                                if(j < ui->editCapacidadeCache->text().toInt()-1){
                                vetLRU[j] = vetLRU[j+1];
                                }//if
                            }//for
                            vetLRU[ui->editCapacidadeCache->text().toInt()-1] = linhaAtual;*/
                            //qDebug()<< "reordenou o hit cache vazia";
                            qDebug()<< vetLRU<< "hit, move "<< linhaAtual << "pro final";
                            break;//i = ui->editCapacidadeCache->text().toInt();
                   }//end if hit cache vazia

               }//end if estado
               if (i >= ui->editCapacidadeCache->text().toInt()-1) {
                       estado = false;
               }
           }//if chegou no final

           if (i == ui->editCapacidadeCache->text().toInt()-1){
               if (!estado){
               //qDebug()<<"Estado da cache = "<< estado;

               for (int j = 0;j <= ui->editCapacidadeCache->text().toInt(); j++) {
                   bool verificador = false;

                   int valorAtual = line.toInt();
                   int valorCache = 0;
                   for(int m = 0; m <= ui->editCapacidadeCache->text().toInt() -1; m++){
                       //qDebug()<< m;
                       valorCache = ui->tableCache->item(m,1)->text().toInt();
                       if ( valorAtual == valorCache){
                           verificador = true;
                           //qDebug() << "é igual?"<< verificador;
                           break;
                       }//if encontra hit
                   }//for encontra hit



                   if (valorCache == valorAtual && verificador == true){// verifica hit na cache cheia
                       hit ++;
                       ui->editHit->setText(QString::number(hit));


                       int indiceVetor = 0;
                       for(int m = 0; m <= ui->editCapacidadeCache->text().toInt() -1; m++){
                           //qDebug()<< m;

                           if ( vetLRU[m] == valorAtual){
                               indiceVetor = m;
                               break;
                           }
                       }
                       int indiceReal = 0;
                       while (indiceReal < ui->editCapacidadeCache->text().toInt()) {
                           if (ui->tableCache->item(indiceReal,1)->text().toInt() == vetLRU[indiceReal]){

                               break;
                           }
                           indiceReal+=1;
                       }

                       ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(QString::number(linhaAtual)));

                       //vetLRU.pop_front();//remove da cabeça
                       //vetLRU.push_back(linhaAtual);//insere na cauda
                       //qDebug()<< vetLRU[j] << "hit cache cheia, valor a ser movido pro final";
                       vetLRU.push_back(linhaAtual);
                       vetLRU.removeAt(indiceVetor);




                       //vetLRU.move(j,ui->editCapacidadeCache->text().toInt()-1);
                       /*for(int j = 0; j < ui->editCapacidadeCache->text().toInt(); j++){
                           if(j < ui->editCapacidadeCache->text().toInt()-1){
                           vetLRU[j] = vetLRU[j+1];
                           }//if
                       }//for
                       vetLRU[ui->editCapacidadeCache->text().toInt()-1] = linhaAtual;*/

                       qDebug()<< vetLRU<< "hit cache cheia, move "<< linhaAtual << "pro final";
                       break;
                   }//end if hit cheio
                   if (valorCache != valorAtual  && verificador == false) {//miss cache cheia
                       miss ++;
                       ui->editMiss->setText(QString::number(miss));

                       int indiceReal = 0;
                       while (indiceReal < ui->editCapacidadeCache->text().toInt()) {
                           if (ui->tableCache->item(indiceReal,1)->text().toInt() == vetLRU[0]){

                               break;
                           }
                           indiceReal+=1;
                       }

                       ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(QString::number(linhaAtual)));
                       vetLRU.pop_front();//remove da cabeça
                       vetLRU.push_back(linhaAtual);//insere na cauda
                       /*for(int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                           if(k < ui->editCapacidadeCache->text().toInt()-1){
                               vetLRU[k] = vetLRU[k+1];
                           }
                       }
                       vetLRU[ui->editCapacidadeCache->text().toInt()-1] = linhaAtual;*/
                       qDebug()<< vetLRU<< "miss cache cheia, insere "<< linhaAtual << "no final";
                       break;
                   }// if miss cheio
               }//for cache cheia
             }//if estado cheio
         }//if for cache cheio
       }//for cache vazia

     }//while
       arquivo.close();

    }//if radio

//-----------------------LFU---------------------
    if (ui->radioAssociativo->isChecked() && ui->radioLFU->isChecked()){


        int contHit[ui->editCapacidadeCache->text().toInt()][ui->editCapacidadeCache->text().toInt()];
        bool estado = true;
        for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
             contHit[k][0] = 0;
             contHit[k][1] = 0;
             qDebug() << contHit[k][0]<< "|" << contHit[k][1];
         }


        qDebug() << "contHit zerado";


        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if
        QTextStream entrada(&arquivo);

        while (!arquivo.atEnd()) {
        QString line = arquivo.readLine();//faz a leitura de uma linha
        qDebug()<<"linha da vez"<<line;

            for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {

                if (i <= ui->editCapacidadeCache->text().toInt()-1){
                    if (estado){
                        qDebug()<<"Estado da cache = "<< estado;
                    if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(line));

                    contHit[i][0] = line.toInt();
                    contHit[i][1] = 0;

                    qDebug() << "substituição por miss em cache vazia / estado da cache";
                    for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                        qDebug() << contHit[k][0] << "|" << contHit[k][1];
                    }
                    break;
                    //i = ui->editCapacidadeCache->text().toInt();

                        // ----------verifica se ja existe na cache----------
                    } else if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() == line) {//verifica se é hit

                        hit ++;
                        ui->editHit->setText(QString::number(hit));
                        qDebug()<<"hit";

                        contHit[i][1] ++;
                        qDebug() << "Hit, incremento de contador/ estado da cache";
                         for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                            qDebug() << contHit[k][0] << "|" << contHit[k][1];
                         }
                         break;
                        //i = ui->editCapacidadeCache->text().toInt();

                         }

                }
                if (i >= ui->editCapacidadeCache->text().toInt()-1) {
                        estado = false;
                }

            }//else {

                    if (i == ui->editCapacidadeCache->text().toInt()-1){
                        if (!estado){
                        qDebug()<<"Estado da cache = "<< estado;
                        //qDebug()<<"linha da vez"<< line;
                        for (int j = 0;j <= ui->editCapacidadeCache->text().toInt(); j++) {


                            bool verificador = false;

                            int valorAtual = line.toInt();
                            int valorCache = 0;
                            for(int m = 0; m <= ui->editCapacidadeCache->text().toInt() -1; m++){
                                qDebug()<< m;
                                valorCache = ui->tableCache->item(m,1)->text().toInt();
                                if ( valorAtual == valorCache){
                                    verificador = true;
                                    qDebug() << "é igual?"<< verificador;
                                    break;
                                }
                            }
                            qDebug() << "Encontrou igual? "<< verificador;
                            valorAtual = line.toInt();
                            valorCache = ui->tableCache->item(j,1)->text().toInt();
                            if (valorCache == valorAtual && verificador == true){
                                hit ++;
                                ui->editHit->setText(QString::number(hit));
                                qDebug()<<"hit";
                                contHit[j][1] ++;
                                qDebug() << "Hit cache cheia, incremento de contador/ estado da cache";
                                for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                                   qDebug() << contHit[k][0] << "|" << contHit[k][1];
                                }//for debug
                                break;
                            }//if igual
                            else if (valorCache != valorAtual  && verificador == false) {
                                //encontra a instrução com menor numero de hit
                                int menor = contHit[0][1];
                                int posicaoMenor = 0;

                                for (int l = 0; l <= ui->editCapacidadeCache->text().toInt(); l++) {
                                    if (contHit[l][1] < menor){
                                        menor = contHit[l][1];
                                        posicaoMenor = l;
                                    }
                                }
                                qDebug() << "menor qtd de hit" << menor;
                                qDebug() << "valor a ser substituido"<< contHit[posicaoMenor][0] << "posição do menor" << posicaoMenor;

                                //incrementa miss e substitui na cache
                                miss ++;
                                ui->editMiss->setText(QString::number(miss));
                                ui->tableCache->setItem(posicaoMenor,1, new QTableWidgetItem(line));//cache recebe o endereço novo na posição salva no vetor
                                contHit[posicaoMenor][0] = line.toInt();
                                contHit[posicaoMenor][1] = 0;

                                qDebug() << "substituição por miss em cache cheia/estado da cache";
                                 for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                                    qDebug() << contHit[k][0] << "|" << contHit[k][1];
                                 }
                                break;
                            }//if diferente
                        }//for cheio
                    }//estado false
                }//if cheio



            }//for


        }//while
        arquivo.close();
    }// if lfu

//--------------------------------------ASSOCIATIVO POR CONJUNTO + RANDOM-------------------------------------
    if(ui->radioAssociativoConjunto->isChecked() && ui->radioRANDOM->isChecked()){

        int qtdLinhaConjunto = ui->editCapacidadeCache->text().toInt() / ui->editConjuntos->text().toInt();// descobre quantas linhas para cada conjunto
        int qtdConjunto = ui->editConjuntos->text().toInt();

        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if

        QTextStream entrada(&arquivo);
        while (!arquivo.atEnd()) {
            QString line = arquivo.readLine();//faz a leitura de uma linha

            int linhaAtual = line.toInt();
            int conjuntoReferencia = linhaAtual % qtdConjunto;// descobre a qual conjunto pertence
            qDebug() << "linha "<< linhaAtual;
            qDebug() << "Vou para o conjunto " << conjuntoReferencia;
            for(int i = conjuntoReferencia*(qtdLinhaConjunto ); i < (conjuntoReferencia +1) * qtdLinhaConjunto; i++ ){

                if (ui->tableCache->item(i,0)->text()== "1" && ui->tableCache->item(i,1)->text() == line) {
                    hit ++;
                    ui->editHit->setText(QString::number(hit));
                    i = ui->editCapacidadeCache->text().toInt();
                }else if(ui->tableCache->item(i,0)->text() == "0"){
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(line));
                    i = ui->editCapacidadeCache->text().toInt();
                }else if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() != line && i == (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                    //int tamanhoRandom = qtdLinhaConjunto;

                    int random = QRandomGenerator::global()->bounded(conjuntoReferencia*(qtdLinhaConjunto -1),(conjuntoReferencia +1) * (qtdLinhaConjunto-1) );
                    qDebug()<<"Numero gerado no random" << random;

                    ui->tableCache->setItem(random,1, new QTableWidgetItem(line));
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                }

            }// end for conjunto
        }//end while
        arquivo.close();
    }


    //------------------------------Associativo por conjunto + FIFO-----------------------------------------
    if(ui->radioAssociativoConjunto->isChecked() && ui->radioFIFO->isChecked()){
        fifo ++;
        int qtdLinhaConjunto = ui->editCapacidadeCache->text().toInt() / ui->editConjuntos->text().toInt();// descobre quantas linhas para cada conjunto
        int qtdConjunto = ui->editConjuntos->text().toInt();
        bool estado = true;
        vet.resize(ui->editCapacidadeCache->text().toInt());
        if (fifo -1 == 0){
            for (int i = 0; i < vet.size(); i++){
                vet[i]= ui->tableCache->item(i,1)->text().toInt();
            }
        }

        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if

        QTextStream entrada(&arquivo);
        while (!arquivo.atEnd()) {
            QString line = arquivo.readLine();//faz a leitura de uma linha

            int linhaAtual = line.toInt();
            int conjuntoReferencia = linhaAtual % qtdConjunto;// descobre a qual conjunto pertence
            qDebug() << "linha "<< linhaAtual;
            qDebug() << "Vou para o conjunto " << conjuntoReferencia;
            for(int i = conjuntoReferencia*(qtdLinhaConjunto ); i < (conjuntoReferencia +1) * qtdLinhaConjunto; i++ ){
                int linhaCache = ui->tableCache->item(i,1)->text().toInt();

                if (i <= (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                    if (estado){
                        if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                            qDebug()<< "verificou se esta vazio, cache vazia";
                            miss ++;
                            ui->editMiss->setText(QString::number(miss));
                            ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                            ui->tableCache->setItem(i,1, new QTableWidgetItem(QString::number(linhaAtual)));
                            vet[i] = linhaAtual;
                            qDebug()<< vet << "miss cache vazia, insere "<< linhaAtual << "no final";
                            break;//i = ui->editCapacidadeCache->text().toInt();
                        }//end if linha vazia
                        else if (ui->tableCache->item(i,0)->text() == "1" && linhaCache == linhaAtual) {//verifica se é hit
                                 qDebug()<< "Verificou se é hit cache vazia";
                                 hit ++;
                                 ui->editHit->setText(QString::number(hit));
                                 qDebug()<< vet << "hit, cache vazia "<< linhaAtual << "";
                                 break;//i = ui->editCapacidadeCache->text().toInt();
                        }//end if hit cache vazia

                    }//end if estado
                    if (i >= (conjuntoReferencia +1) * qtdLinhaConjunto -1) {
                            estado = false;
                    }
                }//if chegou no final

                if (i == (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                    if (!estado){
                    qDebug()<<"Estado da cache = "<< estado;

                    for (int j = conjuntoReferencia*(qtdLinhaConjunto ); j < (conjuntoReferencia +1) * qtdLinhaConjunto; j++ ) {
                        bool verificador = false;

                        int valorAtual = line.toInt();
                        int valorCache = 0;
                        for(int m = conjuntoReferencia*(qtdLinhaConjunto ); m < (conjuntoReferencia +1) * qtdLinhaConjunto; m++){
                            qDebug()<< m;
                            valorCache = ui->tableCache->item(m,1)->text().toInt();
                            if ( valorAtual == valorCache){
                                verificador = true;
                                qDebug() << "é igual?"<< verificador;
                                break;
                            }//if encontra hit
                        }//for encontra hit

                        if (valorCache == valorAtual && verificador == true){// verifica hit na cache cheia
                            hit ++;
                            ui->editHit->setText(QString::number(hit));
                            qDebug()<< vet<< "hit cache cheia"<< linhaAtual << "";
                            break;
                        }//end if hit cheio
                        else if (valorCache != valorAtual  && verificador == false) {//miss cache cheia
                            miss ++;
                            ui->editMiss->setText(QString::number(miss));

                            int indiceReal = conjuntoReferencia*(qtdLinhaConjunto );
                            while (indiceReal < (conjuntoReferencia +1) * qtdLinhaConjunto) {
                                if (ui->tableCache->item(indiceReal,1)->text().toInt() == vet[conjuntoReferencia*(qtdLinhaConjunto )]){
                                    break;
                                }
                                indiceReal++;
                            }

                            ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(QString::number(linhaAtual)));

                            for (int m = conjuntoReferencia*(qtdLinhaConjunto ); m < (conjuntoReferencia +1) * qtdLinhaConjunto; m++){
                                if(m < (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                                    vet[m] = vet[m+1];
                                }
                            };
                            vet[(conjuntoReferencia +1) * qtdLinhaConjunto -1] = linhaAtual;
                            /*vet.removeAt(conjuntoReferencia*(qtdLinhaConjunto));//vet.pop_front();//remove da cabeça
                            vet.insert((conjuntoReferencia +1) * qtdLinhaConjunto,linhaAtual);//vet.push_back(linhaAtual);//insere na cauda
                            */
                            qDebug()<< vet<< "miss cache cheia, insere "<< linhaAtual << "no final";
                            break;
                        }// if miss cheio
                    }//for cache cheia
                  }//if estado cheio
              }//if for cache cheio


            }// end for
        }//end while
        arquivo.close();
    }// end radio fifo


    //------------------------------Associativo por conjunto + LRU-----------------------------------------
    if(ui->radioAssociativoConjunto->isChecked() && ui->radioLRU->isChecked()){
        QVector<int> vetLRU;
        bool estado = true;
        vetLRU.resize(ui->editCapacidadeCache->text().toInt());
        int qtdLinhaConjunto = ui->editCapacidadeCache->text().toInt() / ui->editConjuntos->text().toInt();// descobre quantas linhas para cada conjunto
        int qtdConjunto = ui->editConjuntos->text().toInt();
        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if

        QTextStream entrada(&arquivo);
        while (!arquivo.atEnd()) {
            QString line = arquivo.readLine();//faz a leitura de uma linha

            int linhaAtual = line.toInt();
            int conjuntoReferencia = linhaAtual % qtdConjunto;// descobre a qual conjunto pertence
            qDebug() << "linha "<< linhaAtual;
            qDebug() << "Vou para o conjunto " << conjuntoReferencia;
            for(int i = conjuntoReferencia*(qtdLinhaConjunto ); i < (conjuntoReferencia +1) * qtdLinhaConjunto; i++ ){
                int linhaCache = ui->tableCache->item(i,1)->text().toInt();
                if (i <= (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                    if (estado){
                        if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                         //qDebug()<< "verificou se esta vazio, cache vazia";
                         miss ++;
                         ui->editMiss->setText(QString::number(miss));
                         ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                         ui->tableCache->setItem(i,1, new QTableWidgetItem(QString::number(linhaAtual)));

                         for (int m = conjuntoReferencia*(qtdLinhaConjunto ); m < (conjuntoReferencia +1) * qtdLinhaConjunto; m++){
                             if(m < (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                                 vetLRU[m] = vetLRU[m+1];
                             }
                         };
                         vetLRU[(conjuntoReferencia +1) * qtdLinhaConjunto -1] = linhaAtual;

                         qDebug()<< vetLRU<< "miss cache vazia, insere "<< linhaAtual << "no final";
                         break;//i = ui->editCapacidadeCache->text().toInt();

                        }//end if linha vazia
                        if (ui->tableCache->item(i,0)->text() == "1" && linhaCache == linhaAtual) {//verifica se é hit
                                 //qDebug()<< "Verificou se é hit cache vazia";
                                 hit ++;
                                 ui->editHit->setText(QString::number(hit));

                                 int indiceVetor = 0;
                                 for(int m = conjuntoReferencia*(qtdLinhaConjunto ); m < (conjuntoReferencia +1) * qtdLinhaConjunto; m++){
                                     //qDebug()<< m;

                                     if ( vetLRU[m] == linhaAtual){
                                         indiceVetor++;
                                         break;
                                     }
                                 }

                                 int indiceReal = conjuntoReferencia*(qtdLinhaConjunto );
                                 while (indiceReal < (conjuntoReferencia +1) * qtdLinhaConjunto) {
                                     if (ui->tableCache->item(indiceReal,1)->text().toInt() == vetLRU[conjuntoReferencia*(qtdLinhaConjunto )]){
                                         break;
                                     }
                                     indiceReal++;
                                 }

                                 ui->tableCache->setItem(i,1, new QTableWidgetItem(QString::number(linhaAtual)));
                                 vetLRU.move(i,(conjuntoReferencia +1) * qtdLinhaConjunto -1);

                                 qDebug()<< vetLRU<< "hit, move "<< linhaAtual << "pro final";
                                 break;//i = ui->editCapacidadeCache->text().toInt();
                        }//end if hit cache vazia

                    }//end if estado
                    if (i >= (conjuntoReferencia +1) * qtdLinhaConjunto -1) {
                            estado = false;
                    }
                }//if chegou no final

                if (i == (conjuntoReferencia +1) * qtdLinhaConjunto-1){
                    if (!estado){
                    //qDebug()<<"Estado da cache = "<< estado;

                    for (int j = conjuntoReferencia*(qtdLinhaConjunto ); j < (conjuntoReferencia +1) * qtdLinhaConjunto; j++) {
                        bool verificador = false;

                        int valorAtual = line.toInt();
                        int valorCache = 0;
                        for(int m = conjuntoReferencia*(qtdLinhaConjunto ); m <= (conjuntoReferencia +1) * qtdLinhaConjunto -1; m++){
                            //qDebug()<< m;
                            valorCache = ui->tableCache->item(m,1)->text().toInt();
                            if ( valorAtual == valorCache){
                                verificador = true;
                                //qDebug() << "é igual?"<< verificador;
                                break;
                            }//if encontra hit
                        }//for encontra hit



                        if (valorCache == valorAtual && verificador == true){// verifica hit na cache cheia
                            hit ++;
                            ui->editHit->setText(QString::number(hit));


                            int indiceVetor = 0;
                            for(int m = conjuntoReferencia*(qtdLinhaConjunto ); m <= (conjuntoReferencia +1) * qtdLinhaConjunto -1; m++){
                                //qDebug()<< m;

                                if ( vetLRU[m] == valorAtual){
                                    indiceVetor = m;
                                    break;
                                }
                            }


                            int indiceReal = conjuntoReferencia*(qtdLinhaConjunto );
                            while (indiceReal < (conjuntoReferencia +1) * qtdLinhaConjunto) {
                                if (ui->tableCache->item(indiceReal,1)->text().toInt() == vetLRU[conjuntoReferencia*(qtdLinhaConjunto )]){
                                    break;
                                }
                                indiceReal++;
                            }

                            ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(QString::number(linhaAtual)));
                            vetLRU.move(j,(conjuntoReferencia +1) * qtdLinhaConjunto -1);

                           qDebug()<< vetLRU<< "hit cache cheia, move "<< linhaAtual << "pro final";
                            break;
                        }//end if hit cheio
                        if (valorCache != valorAtual  && verificador == false) {//miss cache cheia
                            miss ++;
                            ui->editMiss->setText(QString::number(miss));

                            int indiceReal = conjuntoReferencia*(qtdLinhaConjunto );
                            while (indiceReal < (conjuntoReferencia +1) * qtdLinhaConjunto) {
                                if (ui->tableCache->item(indiceReal,1)->text().toInt() == vetLRU[conjuntoReferencia*(qtdLinhaConjunto )]){
                                    break;
                                }
                                indiceReal++;
                            }

                            ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(QString::number(linhaAtual)));


                            for (int m = conjuntoReferencia*(qtdLinhaConjunto ); m < (conjuntoReferencia +1) * qtdLinhaConjunto; m++){
                                if(m < (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                                    vetLRU[m] = vetLRU[m+1];
                                }
                            };
                            vetLRU[(conjuntoReferencia +1) * qtdLinhaConjunto -1] = linhaAtual;
                            qDebug()<< vetLRU<< "miss cache cheia, insere "<< linhaAtual << "no final";
                            break;
                        }// if miss cheio
                    }//for cache cheia
                  }//if estado cheio
              }//if for cache cheio



            }// end for
        }//end while
        arquivo.close();
    }//end radio LRU

    //------------------------------Associativo por conjunto + LFU-----------------------------------------
    if(ui->radioAssociativoConjunto->isChecked() && ui->radioLFU->isChecked()){
        int contHit[ui->editCapacidadeCache->text().toInt()][ui->editCapacidadeCache->text().toInt()];
        bool estado = true;
        for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
             contHit[k][0] = 0;
             contHit[k][1] = 0;
             qDebug() << contHit[k][0]<< "|" << contHit[k][1];
         }

        int qtdLinhaConjunto = ui->editCapacidadeCache->text().toInt() / ui->editConjuntos->text().toInt();// descobre quantas linhas para cada conjunto
        int qtdConjunto = ui->editConjuntos->text().toInt();

        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if

        QTextStream entrada(&arquivo);
        while (!arquivo.atEnd()) {
            QString line = arquivo.readLine();//faz a leitura de uma linha

            int linhaAtual = line.toInt();
            int conjuntoReferencia = linhaAtual % qtdConjunto;// descobre a qual conjunto pertence
            qDebug() << "linha "<< linhaAtual;
            qDebug() << "Vou para o conjunto " << conjuntoReferencia;
            for(int i = conjuntoReferencia*(qtdLinhaConjunto ); i < (conjuntoReferencia +1) * qtdLinhaConjunto; i++ ){
                if (i <= (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                    if (estado){
                        qDebug()<<"Estado da cache = "<< estado;
                    if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(line));

                    contHit[i][0] = line.toInt();
                    contHit[i][1] = 0;

                    qDebug() << "substituição por miss em cache vazia / estado da cache";
                    for (int k = conjuntoReferencia*(qtdLinhaConjunto ); k < (conjuntoReferencia +1) * qtdLinhaConjunto; k++){
                        qDebug() << contHit[k][0] << "|" << contHit[k][1];
                    }
                    break;
                    //i = ui->editCapacidadeCache->text().toInt();

                        // ----------verifica se ja existe na cache----------
                    } else if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() == line) {//verifica se é hit

                        hit ++;
                        ui->editHit->setText(QString::number(hit));
                        qDebug()<<"hit";

                        contHit[i][1] ++;
                        qDebug() << "Hit, incremento de contador/ estado da cache";
                        for (int k = conjuntoReferencia*(qtdLinhaConjunto ); k < (conjuntoReferencia +1) * qtdLinhaConjunto; k++){
                            qDebug() << contHit[k][0] << "|" << contHit[k][1];
                        }
                         break;
                        //i = ui->editCapacidadeCache->text().toInt();

                         }

                }
                if (i >= (conjuntoReferencia +1) * qtdLinhaConjunto -1) {
                        estado = false;
                }

            }//else {

                    if (i == (conjuntoReferencia +1) * qtdLinhaConjunto -1){
                        if (!estado){
                        qDebug()<<"Estado da cache = "<< estado;
                        //qDebug()<<"linha da vez"<< line;
                        for (int j = conjuntoReferencia*(qtdLinhaConjunto ); j < (conjuntoReferencia +1) * qtdLinhaConjunto; j++) {


                            bool verificador = false;

                            int valorAtual = line.toInt();
                            int valorCache = conjuntoReferencia*(qtdLinhaConjunto );
                            for(int m = conjuntoReferencia*(qtdLinhaConjunto ); m < (conjuntoReferencia +1) * qtdLinhaConjunto -1; m++){
                                qDebug()<< m;
                                valorCache = ui->tableCache->item(m,1)->text().toInt();
                                if ( valorAtual == valorCache){
                                    verificador = true;
                                    qDebug() << "é igual?"<< verificador;
                                    break;
                                }
                            }
                            qDebug() << "Encontrou igual? "<< verificador;
                            valorAtual = line.toInt();
                            valorCache = ui->tableCache->item(j,1)->text().toInt();
                            if (valorCache == valorAtual && verificador == true){
                                hit ++;
                                ui->editHit->setText(QString::number(hit));
                                qDebug()<<"hit";
                                contHit[j][1] ++;
                                qDebug() << "Hit cache cheia, incremento de contador/ estado da cache";
                                for (int k = conjuntoReferencia*(qtdLinhaConjunto ); k < (conjuntoReferencia +1) * qtdLinhaConjunto; k++){
                                    qDebug() << contHit[k][0] << "|" << contHit[k][1];
                                }//for debug
                                break;
                            }//if igual
                            else if (valorCache != valorAtual  && verificador == false) {
                                //encontra a instrução com menor numero de hit
                                int menor = contHit[conjuntoReferencia*(qtdLinhaConjunto )][1];
                                int posicaoMenor = conjuntoReferencia*(qtdLinhaConjunto );

                                for (int l = conjuntoReferencia*(qtdLinhaConjunto ); l < (conjuntoReferencia +1) * qtdLinhaConjunto; l++) {
                                    if (contHit[l][1] < menor){
                                        menor = contHit[l][1];
                                        posicaoMenor = l;
                                    }
                                }
                                qDebug() << "menor qtd de hit" << menor;
                                qDebug() << "valor a ser substituido"<< contHit[posicaoMenor][0] << "posição do menor" << posicaoMenor;

                                //incrementa miss e substitui na cache
                                miss ++;
                                ui->editMiss->setText(QString::number(miss));
                                ui->tableCache->setItem(posicaoMenor,1, new QTableWidgetItem(line));//cache recebe o endereço novo na posição salva no vetor
                                contHit[posicaoMenor][0] = line.toInt();
                                contHit[posicaoMenor][1] = 0;

                                qDebug() << "substituição por miss em cache cheia/estado da cache";
                                for (int k = conjuntoReferencia*(qtdLinhaConjunto ); k < (conjuntoReferencia +1) * qtdLinhaConjunto; k++){
                                    qDebug() << contHit[k][0] << "|" << contHit[k][1];
                                }
                                break;
                            }//if diferente
                        }//for cheio
                    }//estado false
                }//if cheio



            }//for
        }//end while
        arquivo.close();
    }//end radio lfu



}//end btn










    /*QString concatena = "";
    int row = 0, posicaoDaVirgula = 0;
    QFile arquivo(abrirArquivo);
    if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
        QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
    }
    QTextStream entrada(&arquivo);
    while (!arquivo.atEnd()) {
        QString line = arquivo.readLine();//faz a leitura de uma linha
        for (int c = 0;c < line.length();c++) {//encontra a posição da virgula
            if (line[c] == ","){
                posicaoDaVirgula = c;
            }
        }
        concatena = "";
        for (int i = 0; i < posicaoDaVirgula; i++) {//concatena os dados antes da virgula
            concatena = concatena + line[i];
        }
        ui->tableCache->setItem(row, 0, new QTableWidgetItem(concatena));//adiciona na celula

        concatena = "";

        for (int j = posicaoDaVirgula; j < line.length(); j++) {//concatena os dados depois da virgula
            concatena = concatena + line[j+1];
        }
        ui->tableCache->setItem(row, 1, new QTableWidgetItem(concatena));//adiciona na celula
        row++;

    }*/


