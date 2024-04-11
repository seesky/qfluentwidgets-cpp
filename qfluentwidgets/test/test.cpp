#include <QtWidgets/QLabel>
#include <QtCore/Qt>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QDesktopWidget>

#include "../components/widgets/scroll_area.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建一个窗口
    QWidget window;
    window.resize(400, 200);

    // 创建一个QScrollArea
    ScrollArea *scrollArea = new ScrollArea(&window);
    scrollArea->setWidgetResizable(true); // 允许内容根据尺寸自动调整

    // 创建一个内容widget和布局
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    // 向内容widget添加一些标签作为内容
    for (int i = 0; i < 100; ++i) {
        layout->addWidget(new QLabel(QString("Label %1").arg(i + 1)));
    }

    // 将内容widget设置到滚动区域
    scrollArea->setWidget(contentWidget);

    window.show();
    return app.exec();
}

