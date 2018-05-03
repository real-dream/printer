#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *action_print = new QAction("打印",this);
    QAction *action_printpreview = new QAction("打印预览",this);
    QAction *action_createPDF = new QAction("创建PDF",this);
    connect(action_createPDF,&QAction::triggered,this,&MainWindow::createPDF);
    connect(action_print,&QAction::triggered,this,&MainWindow::dopaint);
    connect(action_printpreview,&QAction::triggered,this,&MainWindow::dopaintpreview);
    ui->mainToolBar->addAction(action_print);
    ui->mainToolBar->addAction(action_printpreview);
    ui->mainToolBar->addAction(action_createPDF);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dopaint()
{
    QPrinter printer;
    QPrintDialog dlg(&printer,this);
    if(ui->textEdit->textCursor().hasSelection())
    {
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }
    if(dlg.exec() == QDialog::Accepted)
    {
        ui->textEdit->print(&printer);
    }
}

void MainWindow::dopaintpreview()
{
    QPrinter printer;
    QPrintPreviewDialog dialog(&printer,this);
    connect(&dialog,&QPrintPreviewDialog::paintRequested,this,&MainWindow::printpreview);
    dialog.exec();
}

void MainWindow::printpreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}

void MainWindow::createPDF()
{
    QString filename = QFileDialog::getOpenFileName(this,"导出文件",QString(),"*.pdf");
    if(!filename.isEmpty())
    {
        if(QFileInfo(filename).suffix().isEmpty())
            filename.append(".pdf");
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        ui->textEdit->print(&printer);
    }
}
