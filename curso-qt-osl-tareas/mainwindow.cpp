#include "mainwindow.h"
#include <QTableWidget>
#include <QSqlTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QSqlQuery>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup database
    ConecToDb(db_, "tareas");

    db_.exec("CREATE TABLE IF NOT EXISTS tareas ("
              "id_tarea INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "date TEXT,"
              "descripcion TEXT,"
              "realizada  INTEGER,"
              "id_categoria  INTEGER"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS categorias ("
              "id_categoria INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "descripcion TEXT"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS etiqueta ("
              "id_etiqueta INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT"
              ");");
    db_.exec("CREATE TABLE IF NOT EXISTS tarea_etiqueta ("
             "id_tarea NOT NULL,"
             "id_etiqueta NOT NULL,"
             "PRIMARY KEY (id_tarea,id_etiqueta)"
              ");");
    QSqlRelationalTableModel* tModelo_ = new QSqlRelationalTableModel(this,db_);
    tModelo_->setTable("tareas");
    tModelo_->setRelation(5,QSqlRelation("categorias","id_categoria","name"));
    tModelo_->select();
    ui->tablewtareas->setModel(tModelo_);
    QSqlRelationalTableModel* tcategorias = new QSqlRelationalTableModel(this,db_);
    tcategorias->setTable(("categorias"));
    tcategorias->select();
    ui->tabvcategorias->setModel(tcategorias);



}

MainWindow::~MainWindow()
{
    delete ui;

}




