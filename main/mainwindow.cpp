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

    

    

#include <KTextEditor/Document>

#include <KTextEditor/View>

#include <KTextEditor/Editor>

#include <KTextEditor/EditorChooser>

    

    

MainWindow::MainWindow(QWidget *)

{

    KTextEditor::Editor *editor = KTextEditor::EditorChooser::editor();

    

    if (!editor) {

    KMessageBox::error(this, i18n("A KDE text-editor component could not be found;\n"

                                "please check your KDE installation."));

    kapp->exit(1);

    }

    

    m_doc = editor->createDocument(0);

    m_view = qobject_cast<KTextEditor::View*>(m_doc->createView(this));

    

    setCentralWidget(m_view);

    setupActions();

    

//       setXMLFile("editorui.rc");

    createShellGUI(true);

    

    guiFactory()->addClient(m_view);

    

    show ();

}

    

void MainWindow::setupActions()

{

    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());

    KStandardAction::open(this, SLOT(openFile()), actionCollection());

    KStandardAction::clear(this, SLOT(clear()), actionCollection());

}

    

void MainWindow::clear()

{

    m_doc->clear();

}

    

void MainWindow::openFile()

{

    m_view->document()->openUrl(KFileDialog::getOpenFileName());

}