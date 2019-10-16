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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ****************************************************************************/

#include <QtDebug>
#include <QMetaProperty>
#include <QPluginLoader>
#include <QDir>
#include <QMetaClassInfo>
#include <QtWidgets/QApplication>

#include "propertyeditor.h"
#include "propertyinterface.h"
#include "propertymodel.h"
#include "propertydelegate.h"

#ifndef LIB_INSTALL_DIR
    #define LIB_INSTALL_DIR "../lib"
#endif

namespace PropertyEditor
{

   PropertyEditor::PropertyEditor
      (
      QWidget *parent
      )
      : QTreeView(parent), m_object(0), m_model(0), m_delegate(0)
   {
      setAlternatingRowColors(true);
      setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
      loadPlugins();
      m_delegate = new PropertyDelegate(this);
      setItemDelegate(m_delegate);
      m_model = new PropertyModel(this, 0, &m_plugins);
      QTreeView::setModel(m_model);
      setSelectionMode(QTreeView::SingleSelection);
      setSelectionBehavior(QTreeView::SelectRows);
      setRootIsDecorated(true);

      setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::SelectedClicked);
   }

   void PropertyEditor::loadPlugins
      (
      )
   {
      QStringList pluginPaths = qApp->libraryPaths();
      {
         QDir pluginsDir = QDir(qApp->applicationDirPath());
         #if defined(Q_OS_WIN)
         if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
            pluginsDir.cdUp();
         #elif defined(Q_OS_MAC)
         if (pluginsDir.dirName() == "MacOS")
         {
            pluginsDir.cdUp();
            pluginsDir.cd("PlugIns");
         }
         #else
         pluginsDir.cd("../lib");
         #endif
         pluginPaths.append(pluginsDir.absolutePath());
      }

      QDir pluginsDir;
      foreach (QString path, pluginPaths)
      {
         pluginsDir = QDir(path);
         if(!pluginsDir.cd("propertyEditor"))
            continue;

         foreach(QFileInfo fileInfo, pluginsDir.entryList(QDir::Files))
         {
            // Ignore PDB files on Windows
            if(fileInfo.suffix().compare("pdb", Qt::CaseInsensitive) == 0)
            {
               continue;
            }
#if _DEBUG
            if(!fileInfo.completeBaseName().endsWith(QString("Propertyd")))
            {
               if(!fileInfo.completeBaseName().endsWith(QString("Property")))
               {
                  qWarning()
                     << QString("Invalid plugin file (ignored): %1").arg(fileInfo.fileName());
               }
               continue;
            }
#else
            if(!fileInfo.completeBaseName().endsWith(QString("Property")))
            {
               if(!fileInfo.completeBaseName().endsWith(QString("Propertyd")))
               {
                  qWarning()
                     << QString("Invalid plugin file (ignored): %1").arg(fileInfo.fileName());
               }
               continue;
            }
#endif
            QPluginLoader loader(pluginsDir.absoluteFilePath(fileInfo.fileName()));
            loader.setLoadHints(QLibrary::ResolveAllSymbolsHint);
            QObject *plugin = loader.instance();
            if (plugin && dynamic_cast<PropertyInterface*>(plugin))
               m_plugins.push_back(dynamic_cast<PropertyInterface*>(plugin));
            else
               qCritical() << plugin << loader.errorString();
         }
      }
   }

   PropertyEditor::~PropertyEditor
      (
      )
   {
   }

   void PropertyEditor::setValidator
      (
      QVariant::Type type,
      PropertyValidator * validator
      )
   {
      m_validators[type]=validator;
   }

   PropertyValidator* PropertyEditor::validator
      (
      QVariant::Type type
      )
   {
      return m_validators[type];
   }

   void PropertyEditor::clearValidators
      (
      )
   {
      m_validators.clear();
   }

   QList<PropertyInterface*>* PropertyEditor::plugins
      (
      )
   {
      return &m_plugins;
   }

   void PropertyEditor::setModel
      (
      PropertyModel * model
      )
   {
      m_model = model;
      QTreeView::setModel(m_model);
   }

   void PropertyEditor::setObject
      (
      QObject * object
      )
   {
      if (object == m_object)
         return;

      m_object = object;
      if (m_model)
         m_model->setObject(object);
      emit(objectChanged(object));
   }

   void PropertyEditor::resetProperties
      (
      )
   {
      if (m_model)
         m_model->resetModel();
   }

   QObject *PropertyEditor::object
      (
      ) const
   {
      return m_object;
   }

}
