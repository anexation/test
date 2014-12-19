//////////////////////////////////////////////////////////////////////////////
// mendaanimationconfigitem.h
// animation configuration item
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo.pereira@free.fr>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#include "mendaconfigdialog.h"
#include "../menda.h"
#include "../config-menda.h"

#include <QApplication>
#include <QIcon>

#include <KLocalizedString>

namespace Menda
{

    int run(int argc, char *argv[])
    {
        QApplication app( argc, argv );
        app.setApplicationName( i18n( "Menda Settings" ) );
        app.setWindowIcon( QIcon::fromTheme( QStringLiteral( "menda" ) ) );
        Menda::ConfigDialog dialog;
        dialog.show();
        bool result = app.exec();
        return result;
    }

}

//__________________________________________
int main(int argc, char *argv[])
{
    #if !MENDA_USE_KDE4
    KLocalizedString::setApplicationDomain("menda_style_config");
    #endif

    return Menda::run( argc, argv );
}
