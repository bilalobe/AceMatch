#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // Populate the language combo box (you can add more languages as needed)
    ui->languageComboBox->addItem("English", "en");
    ui->languageComboBox->addItem("French", "fr");
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getSelectedLanguage() const
{
    return ui->languageComboBox->currentData().toString();
}
