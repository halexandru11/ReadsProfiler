#ifndef FILTERDIALOGBOX_H
#define FILTERDIALOGBOX_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QCheckBox>

#include "mainwindow.h"

class FilterDialogBox : public QDialog
{
public:
    FilterDialogBox(MainWindow* ref);

    void accept();

private:
    static int genresMask;
    static int subgenresMask;
    MainWindow* m_Ref;

    QDialogButtonBox* buttonBox;
    QList<QCheckBox*> genres = {
        new QCheckBox("Fiction"),
        new QCheckBox("Non-fiction"),
        new QCheckBox("Mystery"),
        new QCheckBox("Science fiction")
    };
    QList<QCheckBox*> subgenres = {
        new QCheckBox("Literary fiction"),
        new QCheckBox("Romance"),
        new QCheckBox("Crime/Mystery"),
        new QCheckBox("Science fiction"),
        new QCheckBox("Fantasy"),
        new QCheckBox("Biography/Memoir"),
        new QCheckBox("History"),
        new QCheckBox("Travel"),
        new QCheckBox("Self-help"),
        new QCheckBox("Business"),
        new QCheckBox("Cozy mystery"),
        new QCheckBox("Noir"),
        new QCheckBox("Crime"),
        new QCheckBox("Suspense"),
        new QCheckBox("Thriller"),
        new QCheckBox("Hard science fiction"),
        new QCheckBox("Soft science fiction"),
        new QCheckBox("Space opera"),
        new QCheckBox("Cyberpunk"),
        new QCheckBox("Post-apocalyptic")
    };
};

#endif // FILTERDIALOGBOX_H
