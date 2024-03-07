#include <QtCore/QDate>
#include <QtCore/Qt>
#include <QtCore/QTime>
#include <QtCore/QUrl>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../components/dialog_box/message_box_base.h"
#include "../components/widgets/label.h"
#include "../components/widgets/line_edit.h"
#include "../components/widgets/button.h"
#include "../common/style_sheet.h"


class CustomMessageBox : public MessageBoxBase{
public:
    SubtitleLabel *titleLabel;
    LineEdit *urlLineEdit;

    CustomMessageBox(QWidget *parent) : MessageBoxBase(parent){
        this->titleLabel = new SubtitleLabel(QString("打开 URL"), this);
        this->urlLineEdit = new LineEdit(this);

        this->urlLineEdit->setPlaceholderText(QString("输入文件、流或者播放列表的 URL"));
        this->urlLineEdit->setClearButtonEnabled(true);

        this->viewLayout->addWidget(this->titleLabel);
        this->viewLayout->addWidget(this->urlLineEdit);

        this->yesButton->setText(QString("打开"));
        this->cancelButton->setText(QString("取消"));

        this->widget->setMinimumWidth(350);
        this->yesButton->setDisabled(true);
        connect(this->urlLineEdit, &LineEdit::textChanged, this, &CustomMessageBox::_validateUrl);
    };

public slots:
    void _validateUrl(QString text){
        this->yesButton->setEnabled(QUrl(text).isValid());
    };
};

class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class CustomMessageBoxDemo : public QWidget{
public:
    

    QVBoxLayout *vBoxLayout;
    PushButton *button;

    CustomMessageBoxDemo(){
        this->vBoxLayout = new QVBoxLayout(this);

        this->button = new PushButton(QString("打开 URL"), this, nullptr);
        this->resize(600,  600);
        this->vBoxLayout->addWidget(this->button, 0, Qt::AlignHCenter);
        connect(this->button, &PushButton::clicked, this, &CustomMessageBoxDemo::showDialog);
    }

public slots:
    void showDialog(){
        CustomMessageBox *w = new CustomMessageBox(this);
        if(w->exec()){
            qDebug() << w->urlLineEdit->text();
        }
    };
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    CustomMessageBoxDemo *w = new CustomMessageBoxDemo();
    w->show();
    return app->exec();
}