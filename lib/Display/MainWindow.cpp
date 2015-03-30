#include "QtDisplay/MainWindow.hpp"
// #include <KApplication>
// #include <KAction>
// #include <KLocale>
// #include <KActionCollection>
// #include <KStandardAction>
// #include <KFileDialog>
// #include <KMessageBox>
// #include <KIO/NetAccess>
// #include <KSaveFile>
// #include <QTextStream>
// #include <KXMLGUIFactory>
// #include <KTextEditor/View>
// #include <KTextEditor/Editor>
// #include <KTextEditor/EditorChooser>
// #include <KMenuBar>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include "QtDisplay/SpiderEditor.hpp"
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
//     createShellGUI(true);
// 
//     guiFactory()->addClient(editor->getView());
    this->setMinimumHeight(400);
    this->setMinimumWidth(600);
//     show ();
    rt = new spider::Runtime();
    rt->setShowCallback([&](std::string s){emit output(s.c_str());});
    
}

void MainWindow::setupActions()
{
//     KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
//     KStandardAction::open(this, SLOT(openFile()), actionCollection());
//     KStandardAction::clear(this, SLOT(clear()), actionCollection());
    QAction* runAction = new QAction(QString("IR Execute"), this);
    QAction* compileAction = new QAction(QString("Compile"), this);
    
    QAction* openAction = new QAction(QString("Open"), this);
    QAction* saveAction = new QAction(QString("Save"), this);
    QMenuBar* mb = this->menuBar();
    
    auto fileMenu = mb->addMenu("File");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    
    auto runMenu = mb->addMenu("Run");
    runMenu->addAction(runAction);
    runMenu->addAction(compileAction);
    
    
    connect(editor, SIGNAL(run(const QString&)), this, SLOT(run(const QString&)));
    connect(runAction, SIGNAL(triggered(bool)), editor, SLOT(ktrun()));
    connect(compileAction, SIGNAL(triggered(bool)), this, SLOT(triggerCompile()));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(this, SIGNAL(output(QString)), editor->getOutputPane(), SLOT(append(QString)));
    connect(this, SIGNAL(textEmit(const QString&)), this, SLOT(compile(const QString&)));
}

void MainWindow::clear()
{
    editor->getEditor()->clear();
    
}

void MainWindow::openFile()
{
//     editor->getView()->document()->openUrl(KFileDialog::getOpenFileName());
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        editor->getEditor()->setText(in.readAll());
        file.close();
    }
}
void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName();

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << editor->getEditor()->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void MainWindow::run(const QString& text)
{
    std::istringstream in(text.toStdString());
    try
    {
        while (true)
        {
    //         std::cout << ">> ";
            spider::Statement input(in);

                if (! input.isEmpty())
                    rt->eval(input);
                else break;
        }
    }
    catch (std::exception& e)
    {
        error(e.what());
    }
}

void MainWindow::create(spider::GraphValue* g, spider::Layout* l)
{
    spider::WindowValue* winv = qobject_cast<spider::WindowValue*>(QObject::sender());
    winv->data = new spider::WindowUI(g,l);
}

void MainWindow::error(const QString& s)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText(s);
    msgBox.exec();
}
void MainWindow::compile(const QString& str)
{
    std::cout << "Here" <<std::endl;;
    QProcess process;
    process.start("../spider-compiler/spc - -");
    process.waitForStarted();
    
    process.write(str.toUtf8().constData());
    process.closeWriteChannel();
    process.waitForFinished();
    QByteArray output;
    output = process.readAllStandardOutput();
    QByteArray error = process.readAllStandardError();
//     std::cout << output.toStdString() <<std::endl;
//     editor->getEditor()->setText(output);
    if (error.isEmpty())
    {
        auto newwin = new MainWindow();
        newwin->editor->getEditor()->setText(output);
        newwin->show();
    }
    else editor->getOutputPane()->append(error);
}
void MainWindow::triggerCompile()
{
    emit textEmit((const QString&)editor->getEditor()->toPlainText());
}


