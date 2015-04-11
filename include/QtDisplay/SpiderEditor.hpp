#ifndef SPIDER_QT_EDITOR_HPP
#define SPIDER_QT_EDITOR_HPP
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
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "OutputPane.hpp"
/**
 * \brief - to display all the different componenets of Code Editor.
 * **/
namespace spider
{
    /**
     * \brief - Class to display the different components of Code Editor.
     * The different components consists of the coding area, console output area, single-command execution area 
     * and menu bar.
     * **/
    class EditorWrapper : public QWidget
    {
        Q_OBJECT
    public:
      /** \brief - constructor **/
        EditorWrapper();
//         KTextEditor::View* getView(){return m_view;}
//         KTextEditor::Document* getDocument(){return m_doc;};
	
	/** \brief - function to get the coding area
	 * 
	 * @returns QTextEdit* - the text editor
	 **/
        QTextEdit* getEditor(){return tedit;}
        /**
	 * \brief - function to get console output pane
	 * 
	 * @returns OutputPane* - the console output pane
	 * **/
        OutputPane* getOutputPane(){return pane;}
    private:
//         KTextEditor::View *m_view;
//         KTextEditor::Document *m_doc;
        QTextEdit* tedit;
        QGridLayout* layout;
        QPushButton* pb;
        QLineEdit* le;
        OutputPane* pane;
    private slots:
        void ktrun();
        void lerun();
    signals:
        void run(const QString&);
    };
}

#endif