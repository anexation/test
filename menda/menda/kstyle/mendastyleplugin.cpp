
/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 *************************************************************************/

#include "mendastyleplugin.h"
#include "mendastyleplugin.moc"
#include "mendastyle.h"

#include <QApplication>

namespace Menda
{

    //_________________________________________________
    QStyle* StylePlugin::create( const QString &key )
    {
        if( key.toLower() == QStringLiteral( "menda" ) ) return new Style();
        else return nullptr;
    }

    //_________________________________________________
    StylePlugin::~StylePlugin()
    {
        // Delete style when using ::exit() otherwise it'll outlive the unloaded plugin and we'll get a crash
        if (qApp) delete qApp->style();
    }

    //_________________________________________________
    QStringList StylePlugin::keys() const
    { return QStringList( QStringLiteral( "Menda" ) ); }

}
