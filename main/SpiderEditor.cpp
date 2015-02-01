#include "SpiderEditor.hpp"
#include <QLineEdit>
#include <QPushButton>
namespace spider
{
    EditorWrapper::EditorWrapper()
    {
        KTextEditor::Editor *editor = KTextEditor::EditorChooser::editor();
        if (!editor) {
//                 KMessageBox::error(this, i18n("A KDE text-editor component could not be found;\n"
//                                             "please check your KDE installation."));
            kapp->exit(1);
        }
        m_doc = editor->createDocument(0);
        m_view = qobject_cast<KTextEditor::View*>(m_doc->createView(this));
        
        layout = new QGridLayout(this);
        le = new QLineEdit();
        pb = new QPushButton("Run");

        
        layout->addWidget(m_view, 0, 0, 1, 2);
        layout->addWidget(le, 1, 0);
        layout->addWidget(pb, 1, 1);
        
        connect(le, SIGNAL(returnPressed()), this, SLOT(lerun()));
        connect(pb, SIGNAL(clicked(bool)), this, SLOT(lerun()));
    }
    
    void EditorWrapper::ktrun()
    {
        emit run(m_doc->text());
    }

    void EditorWrapper::lerun()
    {
        emit run(le->text());
        le->clear();
    }

}