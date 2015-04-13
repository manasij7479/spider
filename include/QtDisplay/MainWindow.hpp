#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent=0);
private slots:
    void clear();
    void openFile();
    void saveFile();
    void run(const QString& str);
    void create(GraphValue* g, Layout* l);
    void error(const QString& s);
    void compile(const QString& str);
    void compile_run(const QString& str);
    void triggerCompile();
    void triggerCompileRun();
signals:
    void output(const QString&);
    void textEmitC(const QString&);
    void textEmitR(const QString&);
private:
    void setupActions();
    std::pair<QByteArray, QByteArray> compile_driver(const QString& in);
    spider::EditorWrapper* editor;
    spider::Runtime* rt;
//     QGridLayout* layout;
};

extern MainWindow* mainWin;    

#endif