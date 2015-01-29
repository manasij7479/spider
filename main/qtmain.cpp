#include <KApplication>

#include <KAboutData>

#include <KCmdLineArgs>

    

#include "mainwindow.h"

    

int main (int argc, char *argv[])

{

    KAboutData aboutData( "editor", "editor",

        ki18n("Editor"), "1.0",

        ki18n("A simple text area which can load and save."),

        KAboutData::License_GPL,

        ki18n("Copyright (c) 2007 Developer") );

    KCmdLineArgs::init( argc, argv, &aboutData );

    KApplication app;

    

    MainWindow* window = new MainWindow();

    window->show();

    return app.exec();

}