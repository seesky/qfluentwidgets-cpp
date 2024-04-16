#include "text_interface.h"

TextInterface::TextInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).text, "fluentwidgets.components.widgets", parent)
{
    this->setObjectName("textInterface");

    LineEdit *lineEdit = new LineEdit(this);
    lineEdit->setText(this->tr("ko no dio da！"));
    lineEdit->setClearButtonEnabled(true);
    this->addExampleCard(
        this->tr("A LineEdit with a clear button"),
        lineEdit,
        "http://www.github.com", 0
    );

    SearchLineEdit *searchLineEdit = new SearchLineEdit(this);
    searchLineEdit->setPlaceholderText(this->tr("Type a stand name"));
    searchLineEdit->setClearButtonEnabled(true);
    searchLineEdit->setFixedWidth(230);
    QStringList stands = QStringList();
    stands.append(QString("Star Platinum"));
    stands.append(QString("Hierophant Green"));
    stands.append(QString("Made in Haven"));
    stands.append(QString("Silver Chariot"));
    stands.append(QString("Metallica"));
    stands.append(QString("The Grateful Dead"));

    QCompleter *completer = new QCompleter(stands, searchLineEdit);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setMaxVisibleItems(10);
    searchLineEdit->setCompleter(completer);

    this->addExampleCard(
        this->tr("A autosuggest line edit"),
        searchLineEdit,
        "http://www.github.com", 0
    );

    PasswordLineEdit *passwordLineEdit = new PasswordLineEdit(this);
    passwordLineEdit->setFixedWidth(230);
    passwordLineEdit->setPlaceholderText(this->tr("Enter your password"));
    this->addExampleCard(
        this->tr("A password line edit"),
        passwordLineEdit,
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A SpinBox with a spin button"),
        new SpinBox(this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A DoubleSpinBox with a spin button"),
        new DoubleSpinBox(this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A DateEdit with a spin button"),
        new DateEdit(this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A TimeEdit with a spin button"),
        new TimeEdit(this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A DateTimeEdit with a spin button"),
        new DateTimeEdit(this),
        "http://www.github.com", 0
    );

    TextEdit *textEdit = new TextEdit(this);
    textEdit->setMarkdown(QString("## Steel Ball Run \n * Johnny Joestar 🦄 \n * Gyro Zeppeli 🐴 "));
    this->addExampleCard(
        this->tr("A simple TextEdit"),
        textEdit,
        "http://www.github.com", 1
    );
}