/***************************************************************************
 *   This file is part of the propertyEditor project                       *
 *   Copyright (C) 2008 by BogDan Vatra                                    *
 *   bog_dan_ro@yahoo.com                                                  *
 **                   GNU General Public License Usage                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 **                  GNU Lesser General Public License                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        * 
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library.                                      * 
 *   If not, see <http://www.gnu.org/licenses/>.                           *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ****************************************************************************/

#include <QtCore>
#include <QMetaProperty>
#include <QMetaEnum>
#include <QVector3D>

#include "vector3d.h"

Vector3D::Vector3D(QObject* parent, QObject* object, int property, const PropertyModel* propertyModel): PropertyInterface(parent, object, property, propertyModel)
{
   refreshPropertis(propertyModel);
}

QWidget* Vector3D::createEditor(QWidget * parent, const QModelIndex & index)
{
	Q_UNUSED(index);
	Q_UNUSED(parent);
	return 0;
}

QVariant Vector3D::data(const QModelIndex & index)
{
	if (!index.isValid() || !object() || -1 == objectProperty())
		return QVariant();
	switch (index.column())
	{
		case 0:
			return object()->metaObject()->property(objectProperty()).name();
		case 1:
         {
            QVector3D vec3d = value().value<QVector3D>();
			   return QString("[%1,%2,%3]").arg(vec3d.x()).arg(vec3d.y()).arg(vec3d.z());
         }
	}
	return QVariant();
}

bool Vector3D::setData(QVariant data, const QModelIndex & index)
{
	Q_UNUSED(data);
	Q_UNUSED(index);
	return false;
}

bool Vector3D::canHandle(QObject * object, int property)const
{
	if (object->metaObject()->property(property).isEnumType() || object->metaObject()->property(property).isFlagType())
		return false;

	switch (object->property(object->metaObject()->property(property).name()).type())
	{
		case QVariant::Vector3D:
			return true;
		default:
			return false;
	}
}

Qt::ItemFlags Vector3D::flags(const QModelIndex &/*index*/)
{
	return Qt::ItemIsEnabled;
}

qreal Vector3D::x()
{
	return value().value<QVector3D>().x();
}

void Vector3D::setX(qreal x)
{
	QVector3D s = value().value<QVector3D>();
	s.setX(x);
	setValue(s);
}

qreal Vector3D::y()
{
	return value().value<QVector3D>().y();
}

void Vector3D::setY(qreal y)
{
	QVector3D s = value().value<QVector3D>();
	s.setY(y);
	setValue(s);
}

qreal Vector3D::z()
{
	return value().value<QVector3D>().z();
}

void Vector3D::setZ(qreal z)
{
	QVector3D s = value().value<QVector3D>();
	s.setZ(z);
	setValue(s);
}

PropertyInterface* Vector3D::createInstance(QObject * object, int property, const PropertyModel * propertyModel) const
{
	return new Vector3D(parent(), object, property, propertyModel);
}

Q_EXPORT_PLUGIN2(vector3d, Vector3D);
