/***************************************************************
 *
 * \file jpsgoallistmodel.cpp
 * \date 2019-03-27
 * \version 0.8.8
 * \author Tao Zhong
 * \copyright <2009-2019> Forschungszentrum Jülich GmbH. All rights reserved.
 *
 * \section Lincense
 * This file is part of JuPedSim.
 *
 * JuPedSim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JuPedSim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with JuPedSim. If not, see <http://www.gnu.org/licenses/>.
 *
 * \section Description
 *
 * A simple model that uses a QList<JPSGoal *> as its data source.
****************************************************************/

#include "jpsgoallistmodel.h"

/*!
    Constructs a JPSGoal model with the given parent.
*/

JPSGoalListModel::JPSGoalListModel(QObject *parent)
        : JPSElementListModel(parent)
{
}

/*!
    Constructs a JPSGoal list model containing the specified Goals
    with the given parent.
*/

JPSGoalListModel::JPSGoalListModel(QList<JPSGoal *> &lst, QObject *parent)
        : JPSElementListModel(parent), lst(lst)
{
}

/*!
 When subclassing QAbstractListModel,
 you must provide implementations of the rowCount() and data() functions.
*/

/*!
    Returns data for the specified role, from the item with the given index.

    If the view requests an invalid index, an invalid variant is returned.

    Ovriride from QAbstractListModel
*/

QVariant JPSGoalListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= lst.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return lst.at(index.row())->getCaption();

    return QVariant();
}

/*!
    since 0.8.8


    Returns the number of rows in the model. This value corresponds to the
    number of items in the model's internal Goals list.

    The optional  parent argument is in most models used to specify
    the parent of the rows to be counted. Because this is a list if a
    valid parent is specified, the result will always be 0.

    Hide rowCount() in JPSElementListModel
*/

int JPSGoalListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return lst.count();
}

/*!
 For editable list models, you must also provide an implementation of setData(),
 and implement the flags() function so that it returns a value containing Qt::ItemIsEditable.
*/


/*!
    Sets the data for the specified role in the item with the given
    index in the model, to the provided \a value.

    The dataChanged() signal is emitted if the item is changed.
*/

bool JPSGoalListModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    if (index.row() >= 0 && index.row() < lst.size()
        && (role == Qt::EditRole || role == Qt::DisplayRole))
    {
        const QString valueString = value.toString();

        if (lst.at(index.row())->getCaption() == valueString)
            return true;

        lst.at(index.row())->setCaption(valueString);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }

    return false;
}

/*!
    Returns the flags for the item with the given index.

    Valid items are enabled, selectable, editable, drag enabled and drop enabled.
*/


Qt::ItemFlags JPSGoalListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return JPSElementListModel::flags(index) | Qt::ItemIsDropEnabled;

    return JPSElementListModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

/*!
    Sets the model's internal Goals list to Goals. The model will
    notify any attached views that its underlying data has changed.
*/

void JPSGoalListModel::setGoalsList(QList<JPSGoal *> Goals)
{
    beginResetModel();
    lst = Goals;
    endResetModel();
}

/*!
    Returns the Goals list used by the model to store data.
*/

QList<JPSGoal *> JPSGoalListModel::goalsList()
{
    return lst;
}