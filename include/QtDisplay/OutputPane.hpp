#ifndef SPIDER_OUTPUT_PANE_HPP
#define SPIDER_OUTPUT_PANE_HPP
#include <QLabel>
#include <QTextEdit>
class OutputPane : public QWidget
{
    Q_OBJECT
public:
    OutputPane();
private slots:
    void append(const QString& s);
private:
    QLabel* label;
    QTextEdit* text;
};
#endif