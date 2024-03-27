#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../components/widgets/button.h"
#include "../common/icon.h"
#include "../common/style_sheet.h"
#include "../components/widgets/line_edit.h"

class Demo : public QWidget{
public:

    QHBoxLayout *hBoxLayout;
    SearchLineEdit *lineEdit;
    PushButton *button;
    QCompleter *completer;
    Demo(){
        this->hBoxLayout = new QHBoxLayout(this);
        this->lineEdit = new SearchLineEdit(this);
        this->button = new PushButton(QString("Search"), this, nullptr);

        QStringList stands = QStringList();
        stands.append(QString("Star Platinum"));
        stands.append(QString("Hierophant Green"));
        stands.append(QString("Made in Haven"));
        stands.append(QString("Silver Chariot"));
        stands.append(QString("Metallica"));
        stands.append(QString("The Grateful Dead"));

        this->completer = new QCompleter(stands, this->lineEdit);
        this->completer->setCaseSensitivity(Qt::CaseInsensitive);
        this->completer->setMaxVisibleItems(10);
        this->lineEdit->setCompleter(this->completer);

        this->resize(400, 400);
        this->hBoxLayout->setAlignment(Qt::AlignCenter);
        this->hBoxLayout->addWidget(this->lineEdit, 0, Qt::AlignCenter);
        this->hBoxLayout->addWidget(this->button, 0, Qt::AlignCenter);

        this->lineEdit->setFixedSize(200, 33);
        this->lineEdit->setClearButtonEnabled(true);
        this->lineEdit->setPlaceholderText(QString("Search stand"));
    };

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo *w = new Demo();
    w->show();
    return app->exec();
}