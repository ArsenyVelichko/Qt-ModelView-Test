//
// Created by awesyr on 21.01.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QSplitter>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QGridLayout>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setGeometry(0, 0, 1280, 720);
    setupWidgets();
    setupActions();
}

void MainWindow::setupWidgets() {
    mModel = new QuestionModel(this);
    auto *selectionModel = new QItemSelectionModel(mModel);

    mQuestionList = new QListView;
    mQuestionList->setModel(mModel);
    mQuestionList->setSelectionModel(selectionModel);
    mQuestionList->setEditTriggers(QAbstractItemView::DoubleClicked);

    mQuestionView = new QuestionView;
    mQuestionView->setModel(mModel);
    mQuestionView->setSelectionModel(selectionModel);

    auto* splitter = new QSplitter;
    splitter->addWidget(mQuestionList);
    splitter->addWidget(mQuestionView);
    splitter->setStretchFactor(1, 2);
    splitter->setChildrenCollapsible(false);
    splitter->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);

    mProgressBar = new CircularProgressBar(100);
    mProgressBar->setVisible(false);
    connect(mModel, &QuestionModel::pixmapWritten, mProgressBar, &QProgressBar::setValue);

    auto *gridLayout = new QGridLayout(centralWidget());
    gridLayout->addWidget(splitter, 0, 0);
    gridLayout->addWidget(mProgressBar, 0, 0,  Qt::AlignCenter);
}

void MainWindow::setupActions() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *saveToPdfAction = new QAction(tr("Save to &PDF"));
    connect(saveToPdfAction, &QAction::triggered, this, &MainWindow::saveToPdf);
    fileMenu->addAction(saveToPdfAction);

    QAction *deleteAction = new QAction();
    deleteAction->setShortcut(QKeySequence::Delete);
    connect(deleteAction, &QAction::triggered, mQuestionView, &QuestionView::deleteCurrent);
    addAction(deleteAction);

    QAction *insertAction = new QAction();
    insertAction->setShortcut(QKeySequence::Paste);
    connect(insertAction, &QAction::triggered, mQuestionView, &QuestionView::insertImage);
    addAction(insertAction);
}

void MainWindow::saveToPdf() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/home",tr("(*.pdf)"));
    if (!fileName.isNull()) {
        mProgressBar->setMinimum(0);
        mProgressBar->setMaximum(mModel->rowCount(QModelIndex()) - 1);
        mProgressBar->reset();
        mProgressBar->setVisible(true);

        mModel->writeToPdf(fileName);
        mProgressBar->setVisible(false);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
