#ifndef SPIDER_QT_EDITOR_HPP
#define SPIDER_QT_EDITOR_HPP
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

namespace spider
{
    class EditorWrapper : public QWidget
    {
        Q_OBJECT
    public:
        EditorWrapper();
        KTextEditor::View* getView(){return m_view;}
        KTextEditor::Document* getDocument(){return m_doc;};
    private:
        KTextEditor::View *m_view;
        KTextEditor::Document *m_doc;
    };
}

#endif