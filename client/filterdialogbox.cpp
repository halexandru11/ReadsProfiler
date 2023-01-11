#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>

#include "filterdialogbox.h"
#include "User.h"

int FilterDialogBox::genresMask = 0;
int FilterDialogBox::subgenresMask = 0;

FilterDialogBox::FilterDialogBox(MainWindow* ref) : m_Ref(ref) {
    setWindowTitle("Select filters");
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    for(int bit = 0; bit < 32; ++bit) {
        if(genresMask & (1 << bit)) {
            genres[bit]->setChecked(true);
        }
        if(subgenresMask & (1 << bit)) {
            subgenres[bit]->setChecked(true);
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *checkboxLayout = new QHBoxLayout();

    QGroupBox *col1 = new QGroupBox("Genres");
    QVBoxLayout *col1Layout = new QVBoxLayout();
    for(int i = 0; i < genres.size(); ++i) {
        col1Layout->addWidget(genres[i]);
    }
    col1->setLayout(col1Layout);

    QGroupBox *col2 = new QGroupBox("Subgenres");
    QHBoxLayout *col2Layout = new QHBoxLayout();
    QGroupBox *subCol1 = new QGroupBox();
    QGroupBox *subCol2 = new QGroupBox();
    QVBoxLayout *subCol1Layout = new QVBoxLayout();
    QVBoxLayout *subCol2Layout = new QVBoxLayout();
    for(int i = 0; i < subgenres.size() / 2; ++ i) {
        subCol1Layout->addWidget(subgenres[i]);
    }
    for(int i = subgenres.size() / 2; i < subgenres.size(); ++ i) {
        subCol2Layout->addWidget(subgenres[i]);
    }
    subCol1->setLayout(subCol1Layout);
    subCol2->setLayout(subCol2Layout);
    col2Layout->addWidget(subCol1);
    col2Layout->addWidget(subCol2);
    col2->setLayout(col2Layout);

    checkboxLayout->addWidget(col1);
    checkboxLayout->addWidget(col2);

    QWidget* widget = new QWidget();
    widget->setLayout(checkboxLayout);

    mainLayout->addWidget(widget);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    exec();
}

void FilterDialogBox::accept() {
    for(int bit = 0; bit < genres.size(); ++bit) {
        if(genres[bit]->isChecked()) {
            if((genresMask & (1 << bit)) == 0) {
                genresMask |= (1 << bit);
                MainWindow::client.SetUserModifyGen(genres[bit]->text());
            }
        }
        else {
            if((genresMask & (1 << bit)) != 0) {
                genresMask &= ~(1 << bit);
                MainWindow::client.SetUserModifyGen(genres[bit]->text(), false);
            }
        }
    }
    for(int bit = 0; bit < subgenres.size(); ++bit) {
        if(subgenres[bit]->isChecked()) {
            if((subgenresMask & (1 << bit)) == 0) {
                subgenresMask |= (1 << bit);
                MainWindow::client.SetUserModifySubgen(subgenres[bit]->text());
            }
        }
        else {
            if((subgenresMask & (1 << bit)) != 0) {
                subgenresMask &= ~(1 << bit);
                MainWindow::client.SetUserModifySubgen(subgenres[bit]->text(), false);
            }
        }
    }
    m_Ref->Populate();
    QDialog::accept();
}
