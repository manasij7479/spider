#include "QtDisplay/OutputPane.hpp"
#include <QVBoxLayout>

OutputPane::OutputPane()
{
    QVBoxLayout* layout = new QVBoxLayout();
    label = new QLabel("Console Output");
    text = new QTextEdit();
    text->setReadOnly(true);
    layout->addWidget(label);
    layout->addWidget(text);
    setLayout(layout);
}


void OutputPane::append(const QString& s)
{
    if (text->toPlainText() == "")
        text->setText(s);
    else
        text->setText(text->toPlainText().append("\n").append(s));
}
