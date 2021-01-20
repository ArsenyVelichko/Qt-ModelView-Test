//
// Created by arseny on 06.01.2021.
//

#include "QuestionView.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QGuiApplication>
#include <QClipboard>

QuestionView::QuestionView(QWidget *parent)
    : QScrollArea(parent) {
    setAcceptDrops(true);
    setAlignment(Qt::AlignCenter);

    mImageLabel = new QLabel;
    setWidget(mImageLabel);

    mModel = nullptr;
    mSelectionModel = nullptr;
}

static bool isImageUrl(const QUrl &url) {
    QString localPath = url.toLocalFile();
    QRegExp imageFormats("(.jpeg|.jpg|.png)");
    if (localPath.contains(imageFormats)) {
        return true;
    }
    return false;
}

void QuestionView::dragEnterEvent(QDragEnterEvent *event) {
    auto *mimeData = event->mimeData();
    if (mimeData->hasUrls() && isImageUrl(mimeData->urls()[0])) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void QuestionView::dropEvent(QDropEvent *event) {
    auto *mimeData = event->mimeData();
    if (!mimeData->hasUrls()) { return; }
    if (setupImage(mimeData)) {
        event->acceptProposedAction();
    }
}

void QuestionView::onCurrItemChange(const QModelIndex &current, const QModelIndex &previous) {
    QPixmap pixmap = mModel->data(current, Qt::UserRole).value<QPixmap>();
    mImageLabel->setPixmap(pixmap);
    mImageLabel->resize(pixmap.size());
}

void QuestionView::deleteCurrent() {
    QModelIndex curr = mSelectionModel->currentIndex();
    if (curr.isValid()) {
        mModel->removeRow(curr.row());
    }
}

void QuestionView::insertImage() {
    auto *clipboard = QGuiApplication::clipboard();
    setupImage(clipboard->mimeData());
}

bool QuestionView::setupImage(const QMimeData *mimeData) {
    if (!mimeData->hasUrls()) { return false; }

    QString pixmapPath = mimeData->urls()[0].toLocalFile();
    QPixmap pixmap(pixmapPath);
    if (pixmap.isNull()) { return false; }

    QModelIndex curr = mSelectionModel->currentIndex();
    if (!curr.isValid()) { return false; }

    mModel->setData(curr, pixmap, Qt::UserRole);
    mImageLabel->setPixmap(pixmap);
    mImageLabel->resize(pixmap.size());
    return true;
}

void QuestionView::setModel(QuestionModel *model) {
    mModel = model;
}

void QuestionView::setSelectionModel(QItemSelectionModel *selectionModel) {
    if (mSelectionModel) {
        disconnect(mSelectionModel, &QItemSelectionModel::currentChanged,
                   this, &QuestionView::onCurrItemChange);
    }
    mSelectionModel = selectionModel;
    connect(mSelectionModel, &QItemSelectionModel::currentChanged,
               this, &QuestionView::onCurrItemChange);
}
