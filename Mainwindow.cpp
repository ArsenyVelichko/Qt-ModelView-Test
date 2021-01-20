//
// Created by arseny on 06.01.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include "Mainwindow.h"
#include "QuestionModel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(1280, 720);
    setupWidgets();
    setupActions();
}

void MainWindow::setupWidgets() {
    auto* frame = new QFrame;
    auto* layout = new QHBoxLayout(frame);
    mModel = new QuestionModel(this);

    auto *selectionModel = new QItemSelectionModel(mModel);

    mQuestionList = new QListView;
    mQuestionList->setModel(mModel);
    mQuestionList->setSelectionModel(selectionModel);
    mQuestionList->setFixedWidth(200);
    mQuestionList->setEditTriggers(QAbstractItemView::DoubleClicked);

    mQuestionView = new QuestionView;
    mQuestionView->setModel(mModel);
    mQuestionView->setSelectionModel(selectionModel);
    mQuestionView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(mQuestionList);
    layout->addWidget(mQuestionView);
    setCentralWidget(frame);
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
        mModel->writeToPdf(fileName);
    }
}
