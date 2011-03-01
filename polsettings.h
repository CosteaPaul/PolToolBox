#ifndef POLSETTINGS_H
#define POLSETTINGS_H

#include <QDialog>

namespace Ui {
    class PolSettings;
}

class PolSettings : public QDialog {
    Q_OBJECT
public:
    PolSettings(QWidget *parent = 0);
    ~PolSettings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PolSettings *ui;

private slots:
    void on_PolSettings_accepted();
};

#endif // POLSETTINGS_H
