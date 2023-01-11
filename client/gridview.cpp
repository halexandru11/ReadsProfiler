#include "gridview.h"

#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>

GridView::GridView(QWidget *parent) : QWidget{parent}
{
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget* scrollWidget = new QWidget;
    scrollArea->setWidget(scrollWidget);

    gridLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(gridLayout);

    for (int i = 0; i < numberOfElements; ++i) {
        QLabel* label = new QLabel;
        label->setFixedSize(160,200);
        gridLayout->addWidget(label, i / numberOfCols, i % numberOfCols);
    }

    setLayout(new QVBoxLayout);
    layout()->addWidget(scrollArea);
}

void GridView::resizeEvent(QResizeEvent *event) {
//    int nbCol = event->size().width()/170;
//    if(nbCol == 0) nbCol = 1; // To prevent divide by zero
//    gridLayout->setColumnCount(nbCol);
//    numberOfCols = nbCol;
}
