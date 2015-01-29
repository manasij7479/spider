#include "SpiderEditor.hpp"
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
        }
}