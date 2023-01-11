#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QWidget>
#include <QGridLayout>

class GridView : public QWidget
{
    Q_OBJECT
public:
    explicit GridView(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent* event) override;

private:
    int numberOfElements = 20; // number of elements in grid
    int numberOfCols; // will be calculated based on window width
    QGridLayout* gridLayout;

signals:

};

#endif // GRIDVIEW_H
