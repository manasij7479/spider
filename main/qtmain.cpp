#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include "mainwindow.h"

int main (int argc, char *argv[])
{

    KAboutData aboutData( "spider", "spider",
        ki18n("Spider"), "0.1",
        ki18n("A Graph Visualization Framework"),
        KAboutData::KAboutData::License_GPL_V3,
        ki18n("Copyright (c) 2015 Manasij Mukherjee"));

    KCmdLineArgs::init( argc, argv, &aboutData );

    KApplication app;

    mainWin = new MainWindow();
    
    mainWin->show();

    return app.exec();

}
