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
#include <QTextEdit>
#include <QPushButton>
#include "SpiderEditor.hpp"
#include <iostream>
#include "Runtime/Runtime.hpp"
#include "Runtime/WindowValue.hpp"
MainWindow* mainWin;
MainWindow::MainWindow(QWidget *)
{
    editor = new spider::EditorWrapper();

//     this->setLayout(layout);
    
    setCentralWidget(editor);
    setupActions();
    createShellGUI(true);

    guiFactory()->addClient(editor->getView());
    this->setMinimumHeight(400);
    this->setMinimumWidth(600);
//     show ();
    rt = new spider::Runtime();
    rt->setShowCallback([&](std::string s){emit output(s.c_str());});
    
}

void MainWindow::setupActions()
{
    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
    KStandardAction::open(this, SLOT(openFile()), actionCollection());
    KStandardAction::clear(this, SLOT(clear()), actionCollection());
    KAction* runAction = new KAction(QString("IR Execute"), this);
    KMenuBar* mb = this->menuBar();
    mb->addMenu("Run")->addAction(runAction);
    connect(editor, SIGNAL(run(const QString&)), this, SLOT(run(const QString&)));
    connect(runAction, SIGNAL(triggered(bool)), editor, SLOT(ktrun()));
    connect(this, SIGNAL(output(QString)), editor->getOutputPane(), SLOT(append(QString)));
}

void MainWindow::clear()
{
    editor->getDocument()->clear();
}

void MainWindow::openFile()
{
    editor->getView()->document()->openUrl(KFileDialog::getOpenFileName());
}
void MainWindow::run(const QString& text)
{
    std::istringstream in(text.toStdString());
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

void MainWindow::create(spider::GraphValue* g, spider::Layout<spider::Graph>* l)
{
    spider::WindowValue* winv = qobject_cast<spider::WindowValue*>(QObject::sender());
    winv->data = new spider::WindowUI(g,l);
}