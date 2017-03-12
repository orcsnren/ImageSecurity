#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include <cstdio>
#include "bitmap_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <QtCore>
#include <QtGui>
#include <string>
#include "des2.h"
// Rename this file DES.CPP
// DES Encryption and Decryption
// from efgh.com/software
using namespace std;
QString fileName;
QString XMAX;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Image Security Program ");
    this->setFixedSize(395,270);
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(textChangedSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{

    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Browse..."),
                "C://",
                "Image File(*.bmp)"
                );
if(!fileName.isNull() || !fileName.isEmpty()){
    bitmap_image image(fileName.toStdString());

    QStringList parts = fileName.split("/");
    QString lastBit = parts.at(parts.size()-1);
    QString lastBit2 = parts.at(parts.size()-2);
    QString lastBit3 = parts.at(parts.size()-3);
    QMessageBox::information(this,tr("File Path"),fileName);
    ui->label->setText("../"+lastBit3+"/"+lastBit2+"/"+lastBit);
    ui->lineEdit->setEnabled(true);
    ui->lineEdit->clear();



  /* if (!image)
    {
        QMessageBox::information(this,tr("Warning"),"This does not seem like a valid bitmap image");

    }*/

}else {

    //ui->lineEdit->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->lineEdit->clear();
}

}

void MainWindow::textChangedSlot()
    {
    XMAX = ui->lineEdit->text();
    if(XMAX.length() == 24){
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    }
    else{
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    }
};



void MainWindow::on_pushButton_clicked()
{
    char* path;
    des crypto;
    char *c_maquina1 = new char[fileName.length() + 1];
    strcpy(c_maquina1, fileName.toStdString().c_str());
    char *c_maquina = new char[XMAX.length() + 1];
    strcpy(c_maquina, XMAX.toStdString().c_str());
    path=crypto.do_it(24,c_maquina,c_maquina1,1);
    int u=strlen(path);
    *(path+u)=NULL;
    char c[u];
    int i;
    for(i=0;i<u;i++)
        c[i]=path[i];
    c[u]=NULL;
    //printf("%s",c_maquina);
    QMessageBox::information(this,"Encryption Information","Encryption was successful");
    QMessageBox::information(this,"File Path",c);
}



void MainWindow::on_pushButton_2_clicked()
{

    char *path;
    QString s;
    des crypto;
    char *c_maquina1 = new char[fileName.length() + 1];
    strcpy(c_maquina1, fileName.toStdString().c_str());
    char *c_maquina = new char[XMAX.length() + 1];
    strcpy(c_maquina, XMAX.toStdString().c_str());
    path=crypto.do_it(24,c_maquina,c_maquina1,0);
    int u=strlen(path);
    *(path+u)=NULL;
    char c[u],d[u];
    int i;
    for(i=0;i<u;i++)
        c[i]=path[i];
    for(i=0;i<u;i++)
        d[i]=path[i];
    c[u]=NULL;
    d[u]=NULL;
    //printf("%s",c_maquina);
    QMessageBox::information(this,"Decryption Information", "Decryption was successful");
    QMessageBox::information(this,"File Path", d);
    QDesktopServices::openUrl(QUrl::fromLocalFile(c));
    //cout << path2;

}
