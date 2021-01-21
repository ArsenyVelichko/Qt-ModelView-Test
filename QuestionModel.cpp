//
// Created by arseny on 07.01.2021.
//

#include "QuestionModel.h"
#include <QPixmap>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QImageWriter>
#include <QPdfWriter>
#include <QPainter>

QuestionModel::QuestionModel(QObject *parent) : QAbstractListModel(parent) {
    addQuestion();
}

QuestionModel::QuestionModel(const QString &configPath, QObject *parent)
    : QAbstractListModel(parent) {
    mConfigFilePath = configPath;


}

QVariant QuestionModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    switch (role) {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return mQuestions.value(index.row());

        case Qt::UserRole:
            return mPixmaps.value(index.row());

        default:
            return QVariant();
    }
}

int QuestionModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : mQuestions.size();
}

bool QuestionModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    switch (role) {
        case Qt::EditRole:
            mQuestions[index.row()] = value.toString();

            if (!mQuestions[index.row()].isEmpty() && index.row() == mQuestions.size() - 1)
                addQuestion();

            emit dataChanged(index, index, {Qt::DisplayRole});
            break;

        case Qt::UserRole:
            mPixmaps[index.row()] = value.value<QPixmap>();

            if (index.row() == mQuestions.size() - 1)
                addQuestion();

            emit dataChanged(index, index, {Qt::UserRole});
            break;

        default:
            return false;
    }

    return true;
}

Qt::ItemFlags QuestionModel::flags(const QModelIndex &index) const {
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void QuestionModel::addQuestion() {
    int row = mQuestions.size();
    beginInsertRows(QModelIndex(), row, row);
    mQuestions.append("");
    mPixmaps.append(QPixmap());
    endInsertRows();
}

bool QuestionModel::removeRows(int position, int rows, const QModelIndex &parent) {
    int beginRow = qMax(0, position);
    int endRow = qMin(mQuestions.size() - 1, position + rows);

    beginRemoveRows(QModelIndex(), beginRow, endRow - 1);
    for (int row = beginRow; row < endRow; ++row) {
        mQuestions.removeAt(beginRow);
        mPixmaps.removeAt(beginRow);
    }
    endRemoveRows();

    return true;
}

void QuestionModel::writeToPdf(const QString &pdfFilePath) {
    QPdfWriter writer(pdfFilePath);
    writer.setPageMargins(QMargins());

    qreal writerWidth = writer.width();
    qreal ppi = 72.0;
    qreal scaling = ppi / writer.resolution();

    QPixmap pixmap;
    if (mQuestions.size() > 1) {
        pixmap = mPixmaps[0].scaledToWidth(writerWidth, Qt::SmoothTransformation);
        writer.setPageSize(QPageSize(pixmap.size() * scaling));
    }

    QPainter painter(&writer);

    for (int i = 1; i < mQuestions.size(); i++) {
        painter.drawPixmap(0, 0, pixmap);
        emit pixmapWritten(i);

        if (i < mQuestions.size() - 1) {
            pixmap = mPixmaps[i].scaledToWidth(writerWidth, Qt::SmoothTransformation);
            writer.setPageSize(QPageSize(pixmap.size() * scaling));
            writer.newPage();
        }
    }
}
