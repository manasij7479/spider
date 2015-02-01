#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KParts/MainWindow>
#include <QtGui/QKeyEvent>
#include "SpiderEditor.hpp"
#include <Runtime/GraphValue.hpp>
#include <Layout/Layout.hpp>
#include <QtDisplay/WindowUI.hpp>
#include <QGridLayout>
namespace spider
{
    class Runtime;
}
using namespace spider;
class MainWindow : public KParts::MainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent=0);
private slots:
    void clear();
    void openFile();
    void run(const QString& str);
    void create(GraphValue* g,Layout<Graph>* l);
private:
    void setupActions();
    spider::EditorWrapper* editor;
    spider::Runtime* rt;
//     QGridLayout* layout;
};

extern MainWindow* mainWin;    

#endif