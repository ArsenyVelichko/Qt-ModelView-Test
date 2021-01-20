//
// Created by arseny on 06.01.2021.
//

#include "QuestionView.h"
#include <QDragEnterEvent>
#include <QMimeData>


QuestionView::QuestionView(QuestionModel *model, QWidget *parent)
    : mModel(model), QScrollArea(parent) {
    setAcceptDrops(true);
    setAlignment(Qt::AlignCenter);

    mImageLabel = new QLabel;
    setWidget(mImageLabel);
}


void QuestionView::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void QuestionView::dropEvent(QDropEvent *event) {
    if (!event->mimeData()->hasUrls()) { return; }

    QString pixmapPath = event->mimeData()->urls()[0].toLocalFile();
    QPixmap pixmap(pixmapPath);
    mModel->setData(mCurrentIndex, pixmap, Qt::UserRole);
    mImageLabel->setPixmap(pixmap);
    mImageLabel->resize(pixmap.size());
    event->acceptProposedAction();
}

void QuestionView::onCurrItemChange(const QModelIndex &current, const QModelIndex &previous) {
    mCurrentIndex = current;
    QPixmap pixmap = mModel->data(current, Qt::UserRole).value<QPixmap>();
    mImageLabel->setPixmap(pixmap);
    mImageLabel->resize(pixmap.size());
}
