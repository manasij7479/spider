#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KParts/MainWindow>
#include <QtGui/QKeyEvent>
#include "SpiderEditor.hpp"
namespace spider
{
    class Runtime;
}
class MainWindow : public KParts::MainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent=0);
private slots:
    void clear();
    void openFile();
    void run();
private:
    void setupActions();
    spider::EditorWrapper* editor;
    spider::Runtime* rt;
};

    

#endif