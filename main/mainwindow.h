#ifndef MAINWINDOW_H

#define MAINWINDOW_H

    

#include <KParts/MainWindow>

#include <QtGui/QKeyEvent>

    

    

namespace KTextEditor

{

    class Document;

    class View;

}

    

class MainWindow : public KParts::MainWindow

{

    Q_OBJECT

    

    public:

    MainWindow(QWidget *parent=0);

    

    private slots:

    void clear();

    void openFile();

    

    private:

    void setupActions();

    KTextEditor::View *m_view;

    KTextEditor::Document *m_doc;

};

    

#endif