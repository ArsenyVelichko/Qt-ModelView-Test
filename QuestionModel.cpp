//
// Created by arseny on 07.01.2021.
//

#include "QuestionModel.h"
#include <QPixmap>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QImageWriter>

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

bool QuestionModel::write(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) return false;

    QTextStream textStream(&file);
    QImageWriter imageWriter(&file, "jpg");

    for (int i = 0; i < mQuestions.size() - 1; i++) {
        textStream << mQuestions.at(i);

        QImage image = mPixmaps.at(i).toImage();
        if (!imageWriter.write(image)) {
            return false;
        }
    }
    return true;
}
