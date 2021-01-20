//
// Created by arseny on 06.01.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QAction>
#include <QMenuBar>
#include "Mainwindow.h"
#include "QuestionModel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(1280, 720);
    setupWidgets();
    setupMenus();
}

void MainWindow::setupWidgets() {
    auto* frame = new QFrame;
    auto* layout = new QHBoxLayout(frame);
    mModel = new QuestionModel(this);

    mQuestionList = new QListView;
    mQuestionList->setModel(mModel);
    mQuestionList->setFixedWidth(200);
    mQuestionList->setEditTriggers(QAbstractItemView::DoubleClicked);

    mQuestionView = new QuestionView(mModel);
    mQuestionView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(mQuestionList->selectionModel(), &QItemSelectionModel::currentChanged,
            mQuestionView, &QuestionView::onCurrItemChange);

    layout->addWidget(mQuestionList);
    layout->addWidget(mQuestionView);
    setCentralWidget(frame);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Delete: {
            QModelIndex curr = mQuestionList->currentIndex();
            if (curr.isValid()) {
                mModel->removeRow(curr.row());
            }
            break;
        }
        default:
            break;
    }
}

void MainWindow::setupMenus() {
    QMenu *fileMenu = new QMenu(tr("&File"), this);

    QAction *saveAction = fileMenu->addAction(tr("&Save As..."));
    saveAction->setShortcuts(QKeySequence::SaveAs);

    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    menuBar()->addMenu(fileMenu);
}

void MainWindow::save() {
    mModel->write("out.txt");
}
