#include "mainwindow.h"
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <KFileDialog>
#include <KMessageBox>
#include <KIO/NetAccess>
#include <KSaveFile>
#include <QTextStream>
#include <KXMLGUIFactory>
#include <KTextEditor/View>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>
#include <KMenuBar>
#include "SpiderEditor.hpp"
#include <iostream>
#include "Runtime/Runtime.hpp"
MainWindow::MainWindow(QWidget *)
{
    editor = new spider::EditorWrapper();
    setCentralWidget(editor->getView());
    setupActions();

    createShellGUI(true);

    guiFactory()->addClient(editor->getView());
    this->setMinimumHeight(400);
    this->setMinimumWidth(600);
//     show ();
    rt = new spider::Runtime();
}

void MainWindow::setupActions()
{
    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
    KStandardAction::open(this, SLOT(openFile()), actionCollection());
    KStandardAction::clear(this, SLOT(clear()), actionCollection());
    KAction* runAction = new KAction(QString("IR Execute"), this);
    KMenuBar* mb = this->menuBar();
    mb->addMenu("Run")->addAction(runAction);
    connect(runAction, SIGNAL(triggered(bool)), this, SLOT(run()));
}

void MainWindow::clear()
{
    editor->getDocument()->clear();
}

void MainWindow::openFile()
{
    editor->getView()->document()->openUrl(KFileDialog::getOpenFileName());
}
void MainWindow::run()
{
    std::istringstream in(editor->getDocument()->text().toStdString());
    while (true)
    {
//         std::cout << ">> ";
        spider::Statement input(in);
        try
        {
            if (! input.isEmpty())
                rt->eval(input);
            else break;
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: " << e.what();
        }
    }
}