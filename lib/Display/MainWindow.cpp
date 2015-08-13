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
    clearFlag = false;
    rt = nullptr;
}

void MainWindow::setupActions()
{
//     KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
//     KStandardAction::open(this, SLOT(openFile()), actionCollection());
//     KStandardAction::clear(this, SLOT(clear()), actionCollection());
    QAction* runAction = new QAction(QString("IR Execute"), this);
    QAction* compileAction = new QAction(QString("Compile"), this);
    QAction* compileRunAction = new QAction(QString("Compile and Run"), this);
    
    QAction* openAction = new QAction(QString("Open"), this);
    QAction* saveAction = new QAction(QString("Save"), this);
    QAction *clearAction = new QAction(QString("Clear"), this);
    QMenuBar* mb = this->menuBar();
    mb->setNativeMenuBar(false);
    
    
    auto fileMenu = mb->addMenu("File");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    
    auto runMenu = mb->addMenu("Run");
    runMenu->addAction(runAction);
    runMenu->addAction(compileAction);
    runMenu->addAction(compileRunAction);
    
    auto optionsMenu = mb->addMenu("Options");
    optionsMenu->addAction(clearAction);
    
    
    connect(editor, SIGNAL(run(const QString&)), this, SLOT(run(const QString&)));
    connect(runAction, SIGNAL(triggered(bool)), editor, SLOT(ktrun()));
    connect(compileAction, SIGNAL(triggered(bool)), this, SLOT(triggerCompile()));
    connect(compileRunAction, SIGNAL(triggered(bool)), this, SLOT(triggerCompileRun()));
    connect(clearAction, SIGNAL(triggered(bool)), this, SLOT(setClear()));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(this, SIGNAL(output(QString)), editor->getOutputPane(), SLOT(append(QString)));
    connect(this, SIGNAL(textEmitC(const QString&)), this, SLOT(compile(const QString&)));
    connect(this, SIGNAL(textEmitR(const QString&)), this, SLOT(compile_run(const QString&)));
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
    if (rt == nullptr)
        rt = new spider::Runtime();
    if (clearFlag == true)
    {
        delete rt;
        rt = new spider::Runtime();
        clearFlag = false;
    }
    rt->setShowCallback([&](std::string s){emit output(s.c_str());});
    rt->setReadCallback([this](std::string s)
    {
        bool ok;
        std::string result = QInputDialog::getText(this, tr("Input!"),
                                         QString(s.c_str()), QLineEdit::Normal,
                                         "", &ok).toStdString();
        return result;
    });
//     std::cerr << text.toStdString();
    std::istringstream in(text.toStdString());
    try
    {
        while (true)
        {
            spider::Statement input(in);

            if (! input.isEmpty())
            {
                rt->eval(input);
            }
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
    QByteArray output, error;
    std::tie(output, error) = compile_driver(str);
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
    emit textEmitC((const QString&)editor->getEditor()->toPlainText());
}
void MainWindow::triggerCompileRun()
{
    emit textEmitR((const QString&)editor->getEditor()->toPlainText());
}
std::pair<QByteArray, QByteArray> MainWindow::compile_driver(const QString& in)
{
    QProcess process;
    process.start("../spider-compiler/spc - -");
    process.waitForStarted();
    
    process.write(in.toUtf8().constData());
    process.closeWriteChannel();
    process.waitForFinished();
    QByteArray output;
    output = process.readAllStandardOutput();
    QByteArray error = process.readAllStandardError();
    return {output, error};
}

void MainWindow::compile_run(const QString& str)
{
    QByteArray output, error;
    std::tie(output, error) = compile_driver(str);
    if (error.isEmpty())
        run(output);
    else
        editor->getOutputPane()->append(error);
}
void MainWindow::setClear()
{
    clearFlag = true;
}


