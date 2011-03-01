#include "polsettings.h"
#include "ui_polsettings.h"
#include "qsettings.h"

PolSettings::PolSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PolSettings)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_PolSettings_accepted()));
    //Load values
    QSettings settings;
    ui->Edit_LabelLogin->setText(settings.value("connect","").toString());
}

PolSettings::~PolSettings()
{
    delete ui;
}

void PolSettings::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
  * Write settings
  */
void PolSettings::on_PolSettings_accepted()
{
    QSettings settings;
    settings.setValue("connect",ui->Edit_LabelLogin->text());
}
