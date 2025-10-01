# QFluentWidgets 测试组件使用文档 / QFluentWidgets Test Component Guide

## 简介 Introduction

- 中文：本文档汇总 `qfluentwidgets/test` 目录下的所有测试示例，说明每个组件演示窗口的用途、布局要点以及运行方法，方便在本地快速体验 QFluentWidgets 的功能。各测试均在 CMake 项目中以独立的可执行程序形式提供。
- English: This guide covers every demo under `qfluentwidgets/test`, explaining what each showcase window does, how its layout is organised, and how to run it locally. Every demo is exposed as its own executable target in the CMake project.

### 构建与运行 Build & Run

1. `cmake -S . -B build`
2. `cmake --build build --target <目标名 / target-name>`
3. 在生成目录运行可执行文件：`./build/<目标名 / target-name>`

CMakeLists.txt 为每个测试注册了独立的 target，例如 `button_test`、`check_box_test`、`calendar_picker_test`、`gallery` 等，均链接到核心组件源码和 Qt 依赖。引用对应段落即可确认目标名称。【F:CmakeLists.txt†L40-L1432】

> 下文每节均采用“中文说明 + English description + 运行方式”三段结构。

## Acrylic Brush (`acrylic_brush_test.cpp`)
- 中文：`AcrylicBrushDemo` 使用 `AcrylicBrush` 创建圆形裁剪区域并叠加背景图像，展示亚克力模糊效果和自定义裁剪路径设置。【F:qfluentwidgets/test/acrylic_brush_test.cpp†L10-L31】
- English: `AcrylicBrushDemo` instantiates `AcrylicBrush` with a circular clip path and a custom background pixmap to demonstrate acrylic blur rendering and path clipping.【F:qfluentwidgets/test/acrylic_brush_test.cpp†L10-L31】
- 运行 Run：`cmake --build build --target acrylic_brush_test && ./build/acrylic_brush_test`。【F:CmakeLists.txt†L476-L498】

## Acrylic Combo Box (`acrylic_combo_box_test.cpp`)
- 中文：该文件目前为空，CMake 中对应的 `acrylic_combo_box_test` 目标也被注释掉，提示此示例尚未提供具体实现。【a38057†L1-L2】【F:CmakeLists.txt†L502-L524】
- English: The file is empty and the `acrylic_combo_box_test` target is commented out in CMake, indicating that no demo is available yet.【a38057†L1-L2】【F:CmakeLists.txt†L502-L524】
- 运行 Run：暂无；需补全示例并在 CMake 中启用目标后才能执行。Currently unavailable; implement the demo and re-enable the target before building.

## Acrylic Flyout (`acrylic_flyout_test.cpp`)
- 中文：示例通过三个按钮演示亚克力飞出层的多种创建方式，包括传入标题、正文、图标与自定义内容视图，并连接按钮点击事件触发不同的动画效果。【F:qfluentwidgets/test/acrylic_flyout_test.cpp†L7-L117】
- English: The demo wires three buttons to show acrylic flyouts, covering title/body/icon payloads, embedding custom widgets, and switching between pull-up and drop-down animations.【F:qfluentwidgets/test/acrylic_flyout_test.cpp†L7-L117】
- 运行 Run：`cmake --build build --target acrylic_flyout_test && ./build/acrylic_flyout_test`。【F:CmakeLists.txt†L452-L472】

## Avatar Widget (`avatar_widget_test.cpp`)
- 中文：`AvatarWidgetView` 读取同一张头像图并创建不同半径的 `AvatarWidget`，让布局横向展示多尺寸圆形头像效果。【F:qfluentwidgets/test/avatar_widget_test.cpp†L10-L29】
- English: `AvatarWidgetView` loads a pixmap once and instantiates several `AvatarWidget` instances with varying radii to showcase multiple avatar sizes in a horizontal layout.【F:qfluentwidgets/test/avatar_widget_test.cpp†L10-L29】
- 运行 Run：`cmake --build build --target avatar_widget_test && ./build/avatar_widget_test`。【F:CmakeLists.txt†L526-L548】

## Breadcrumb Bar (`breadcrumb_bar_test.cpp`)
- 中文：示例将 `BreadcrumbBar` 与 `QStackedWidget` 配合，通过输入框新增页面并自动切换内容，同时设定字体、间距等外观细节，演示路径导航的动态维护。【F:qfluentwidgets/test/breadcrumb_bar_test.cpp†L20-L90】
- English: The demo combines `BreadcrumbBar` with a `QStackedWidget`, adding new pages from an input field and swapping the stack when the current breadcrumb changes, while tweaking typography and spacing for a polished navigation trail.【F:qfluentwidgets/test/breadcrumb_bar_test.cpp†L20-L90】
- 运行 Run：`cmake --build build --target breadcrumb_bar_test && ./build/breadcrumb_bar_test`。【F:CmakeLists.txt†L632-L705】

## Buttons (`button_test.cpp`)
- 中文：`ButtonDemo` 通过栅格布局集中展示按钮家族，包括普通、主色、透明、切换、下拉、分裂、药丸等 Push/Tool/Button 变体，并为下拉按钮配备共享菜单动作，方便对比不同风格与交互。【F:qfluentwidgets/test/button_test.cpp†L70-L219】
- English: `ButtonDemo` uses a grid layout to showcase the full button family—standard, primary, transparent, toggle, drop-down, split, and pill variants across push and tool buttons—while wiring a shared menu for drop-down actions to compare styling and behaviour.【F:qfluentwidgets/test/button_test.cpp†L70-L219】
- 运行 Run：`cmake --build build --target button_test && ./build/button_test`。【F:CmakeLists.txt†L40-L72】

## Calendar Picker (`calendar_picker_test.cpp`)
- 中文：示例将 `CalendarPicker` 居中放入水平布局，展示日期选择器默认交互及高 DPI 设置调整。【F:qfluentwidgets/test/calendar_picker_test.cpp†L16-L45】
- English: The sample centres a `CalendarPicker` inside a horizontal layout to present the default calendar selection behaviour alongside the usual high-DPI application flags.【F:qfluentwidgets/test/calendar_picker_test.cpp†L16-L45】
- 运行 Run：`cmake --build build --target calendar_picker_test && ./build/calendar_picker_test`。【F:CmakeLists.txt†L200-L222】

## Card Widgets (`card_widget_test.cpp`)
- 中文：文件定义多种卡片场景，包括具备菜单的 `AppCard`、展示头像和文字的 `EmojiCard`、统计信息组合的 `AppInfoCard`，以及附带翻页视图、描述和系统要求的不同 Header 卡片，同时实现带亚克力遮罩与动画的 `LightBox`，全面演示卡片生态的排版与交互。【F:qfluentwidgets/test/card_widget_test.cpp†L39-L360】
- English: The sample assembles a suite of card experiences—`AppCard` with context menus, icon-centric `EmojiCard`, the statistics-rich `AppInfoCard`, gallery/description/system requirement header cards, and an acrylic `LightBox` overlay with animations—covering layout composition and interactive patterns across the card widget family.【F:qfluentwidgets/test/card_widget_test.cpp†L39-L360】
- 运行 Run：`cmake --build build --target card_widget_test && ./build/card_widget_test`。【F:CmakeLists.txt†L1156-L1178】

## Check Box (`check_box_test.cpp`)
- 中文：`CheckBoxDemo` 将单个 `CheckBox` 居中展示，可作为绑定信号或样式扩展的基础模板。【F:qfluentwidgets/test/check_box_test.cpp†L15-L52】
- English: `CheckBoxDemo` centres a single `CheckBox`, serving as a minimal template for signal wiring or styling experiments.【F:qfluentwidgets/test/check_box_test.cpp†L15-L52】
- 运行 Run：`cmake --build build --target check_box_test && ./build/check_box_test`。【F:CmakeLists.txt†L74-L106】

## Color Dialog (`color_dialog_test.cpp`)
- 中文：`ColorDialogDemo` 通过 `ColorPickerButton` 演示调色板弹窗的呼出与初始颜色设定，垂直居中布局便于在不同主题下观察效果。【F:qfluentwidgets/test/color_dialog_test.cpp†L18-L45】
- English: `ColorDialogDemo` shows how `ColorPickerButton` launches the colour dialog with a preset value, positioning the control centrally to observe theme reactions.【F:qfluentwidgets/test/color_dialog_test.cpp†L18-L45】
- 运行 Run：`cmake --build build --target color_dialog_test && ./build/color_dialog_test`。【F:CmakeLists.txt†L232-L254】

## Combo Box (`combo_box_test.cpp`)
- 中文：`ComBoxDemo` 设置带占位文本的 `ComboBox`，填充自定义字符串列表并监听 `currentTextChanged` 打印结果，用于验证下拉选择的信号输出。【F:qfluentwidgets/test/combo_box_test.cpp†L15-L65】
- English: `ComBoxDemo` configures a `ComboBox` with placeholder text, populates it from a custom string list, and logs `currentTextChanged` signals to validate selection handling.【F:qfluentwidgets/test/combo_box_test.cpp†L15-L65】
- 运行 Run：`cmake --build build --target combo_box_test && ./build/combo_box_test`。【F:CmakeLists.txt†L108-L140】

## Command Bar (`command_bar_test.cpp`)
- 中文：`CommandBarsView1` 构造工具栏并添加可见与隐藏动作、下拉菜单及编辑状态切换，`CommandBarsView2` 则在无边框窗口中点击图片弹出 `CommandBarView` 飞出层，展示命令条的多种布署方式。【F:qfluentwidgets/test/command_bar_test.cpp†L17-L200】
- English: `CommandBarsView1` builds a toolbar with visible and hidden actions plus a drop-down menu and edit toggling, while `CommandBarsView2` shows how to spawn a `CommandBarView` flyout from an image inside a frameless window, covering multiple deployment patterns.【F:qfluentwidgets/test/command_bar_test.cpp†L17-L200】
- 运行 Run：`cmake --build build --target command_bar_test && ./build/command_bar_test`。【F:CmakeLists.txt†L578-L600】

## Custom Message Box (`custom_message_box_test.cpp`)
- 中文：`CustomMessageBox` 继承 `MessageBoxBase`，添加 URL 输入框并在文本校验后启用确认按钮；演示窗口通过按钮点击弹出该对话框并读取用户输入。【F:qfluentwidgets/test/custom_message_box_test.cpp†L15-L74】
- English: `CustomMessageBox` extends `MessageBoxBase` with a URL field that toggles the confirm button based on validation, while the demo window launches the dialog on button press and prints the accepted value.【F:qfluentwidgets/test/custom_message_box_test.cpp†L15-L74】
- 运行 Run：`cmake --build build --target custom_message_box_test && ./build/custom_message_box_test`。【F:CmakeLists.txt†L256-L280】

## Dialog (`dialog_test.cpp`)
- 中文：点击主按钮会弹出 `Dialog`，询问是否删除文件夹并根据返回值打印不同的调试信息，可用于验证标准对话框的按钮回调。【F:qfluentwidgets/test/dialog_test.cpp†L22-L63】
- English: Pressing the primary button spawns a `Dialog` that asks for confirmation and logs which button was pressed, illustrating the default dialog workflow.【F:qfluentwidgets/test/dialog_test.cpp†L22-L63】
- 运行 Run：`cmake --build build --target dialog_test && ./build/dialog_test`。【F:CmakeLists.txt†L282-L306】

## Flip View (`flip_view_test.cpp`)
- 中文：`CustomFlipItemDelegate` 自定义翻页项绘制叠加文字遮罩，`Demo` 将 `HorizontalFlipView` 与 `HorizontalPipsPager` 互相绑定，展示图片轮播与分页联动效果。【F:qfluentwidgets/test/flip_view_test.cpp†L21-L89】
- English: `CustomFlipItemDelegate` overlays text on each slide, while `Demo` synchronises `HorizontalFlipView` with a `HorizontalPipsPager` to demonstrate linked image carousel navigation.【F:qfluentwidgets/test/flip_view_test.cpp†L21-L89】
- 运行 Run：`cmake --build build --target flip_view_test && ./build/flip_view_test`。【F:CmakeLists.txt†L1182-L1204】

## Flow Layout (`flow_layout_test.cpp`)
- 中文：`FlowLayoutView` 开启动画和自定义间距，将多个 `QPushButton` 填入流式布局，演示控件随容器宽度自动换行的效果。【F:qfluentwidgets/test/flow_layout_test.cpp†L9-L48】
- English: `FlowLayoutView` enables animations and custom spacing while populating several `QPushButton` widgets, highlighting how the flow layout wraps content responsively.【F:qfluentwidgets/test/flow_layout_test.cpp†L9-L48】
- 运行 Run：`cmake --build build --target flow_layout_test && ./build/flow_layout_test`。【F:CmakeLists.txt†L429-L449】

## Flyout (`flyout_test.cpp`)
- 中文：借助三个按钮演示 `Flyout` 的标题正文、图标、额外控件与动画方向配置，并在第二个示例中监听关闭信号主动销毁飞出层。【F:qfluentwidgets/test/flyout_test.cpp†L9-L119】
- English: Three buttons showcase how to configure `Flyout` titles, icons, custom widgets, and animation directions, with the second case connecting the view’s close signal to dispose of the flyout instance.【F:qfluentwidgets/test/flyout_test.cpp†L9-L119】
- 运行 Run：`cmake --build build --target flyout_test && ./build/flyout_test`。【F:CmakeLists.txt†L308-L330】

## Folder List Dialog (`folder_list_dialog_test.cpp`)
- 中文：`FolderListDialogDemo` 预填两个本地路径并调用 `FolderListDialog`，监听 `folderChanged` 信号打印用户选择的目录列表，用于构建音乐库等场景。【F:qfluentwidgets/test/folder_list_dialog_test.cpp†L16-L47】
- English: `FolderListDialogDemo` seeds two folder paths, invokes `FolderListDialog`, and logs the `folderChanged` signal to observe user selections, matching use cases such as building a music library.【F:qfluentwidgets/test/folder_list_dialog_test.cpp†L16-L47】
- 运行 Run：`cmake --build build --target folder_list_dialog_test && ./build/folder_list_dialog_test`。【F:CmakeLists.txt†L360-L380】

## Gallery 应用 (`gallery_test.cpp` 与 `gallery/`)
- 中文：`gallery_test.cpp` 根据配置项设置 DPI 缩放并加载多语言翻译，然后启动 `MainWindow`，该窗口创建涵盖基础输入、日期时间、导航、滚动、状态、设置等子界面，并在导航视图中注册图标、头像和下方的设置入口，展示完整的 Fluent Design 画廊体验。【F:qfluentwidgets/test/gallery_test.cpp†L1-L62】【F:qfluentwidgets/test/gallery/view/main_window.cpp†L3-L197】
- English: `gallery_test.cpp` configures DPI scaling from settings, installs translators, and launches `MainWindow`, which wires up sub-interfaces for basic inputs, date & time, dialogs, layout, navigation, scroll, status info, text, view, and settings, adding icons and an avatar to the navigation pane for a full Fluent Design gallery showcase.【F:qfluentwidgets/test/gallery_test.cpp†L1-L62】【F:qfluentwidgets/test/gallery/view/main_window.cpp†L3-L197】
- 运行 Run：`cmake --build build --target gallery && ./build/gallery`（Windows 子系统可直接双击 GUI）。【F:CmakeLists.txt†L1399-L1432】

## Info Badge (`info_badge_test.cpp`)
- 中文：示例分三行展示数字、点状与图标信息徽章的工厂方法，并将成功徽章附着在工具按钮上，涵盖定位、配色和图标自定义用法。【F:qfluentwidgets/test/info_badge_test.cpp†L14-L93】
- English: The demo arranges numeric, dot, and icon info badges using the factory helpers, also attaching a success badge to a tool button to cover positioning, colour, and icon customisation.【F:qfluentwidgets/test/info_badge_test.cpp†L14-L93】
- 运行 Run：`cmake --build build --target info_badge_test && ./build/info_badge_test`。【F:CmakeLists.txt†L709-L731】

## Info Bar (`info_bar_test.cpp`)
- 中文：五个按钮分别触发信息、成功、警告、错误以及自定义 InfoBar，演示不同方向、位置、持续时间和附加控件的配置方式。【F:qfluentwidgets/test/info_bar_test.cpp†L14-L82】
- English: Five buttons spawn information, success, warning, error, and custom InfoBars, covering orientation, placement, duration, and adding extra widgets to the banner.【F:qfluentwidgets/test/info_bar_test.cpp†L14-L82】
- 运行 Run：`cmake --build build --target info_bar_test && ./build/info_bar_test`。【F:CmakeLists.txt†L735-L757】

## Labels (`label_test.cpp`)
- 中文：示例创建超链接、Caption、Body、Subtitle、Title、Display 等多种标签类型，方便对比字号与样式差异。【F:qfluentwidgets/test/label_test.cpp†L15-L36】
- English: The demo instantiates hyperlink, caption, body, subtitle, title, and display labels to compare typography variants side by side.【F:qfluentwidgets/test/label_test.cpp†L15-L36】
- 运行 Run：`cmake --build build --target label_test && ./build/label_test`。【F:CmakeLists.txt†L868-L890】

## Line Edit (`line_edit_test.cpp`)
- 中文：`SearchLineEdit` 配合 `QCompleter` 提供模糊搜索列表，设置清除按钮和占位文本，旁侧配有搜索按钮模拟常见搜索框布局。【F:qfluentwidgets/test/line_edit_test.cpp†L14-L47】
- English: The demo wires a `SearchLineEdit` to a case-insensitive `QCompleter`, enabling the clear button and placeholder text while pairing it with a search push button for a typical query bar layout.【F:qfluentwidgets/test/line_edit_test.cpp†L14-L47】
- 运行 Run：`cmake --build build --target line_edit_test && ./build/line_edit_test`。【F:CmakeLists.txt†L894-L916】

## List View (`list_view_test.cpp`)
- 中文：`ListWidget` 加载大量替身名称，验证 Fluent 样式的列表部件滚动与选中效果，同时设置背景色和边距。【F:qfluentwidgets/test/list_view_test.cpp†L14-L55】
- English: The demo populates `ListWidget` with numerous stand names to inspect scrolling and selection under Fluent styling while customising background colour and margins.【F:qfluentwidgets/test/list_view_test.cpp†L14-L55】
- 运行 Run：`cmake --build build --target list_view_test && ./build/list_view_test`。【F:CmakeLists.txt†L1208-L1230】

## Login Window (`login_window.cpp`/`.h`)
- 中文：`LoginWindow` 继承 `AcrylicWindow`，在 `setupUi` 中构造左右分栏界面：左侧展示背景图，右侧包含 FTP 登录表单（主机、端口、用户名、密码）、记住密码复选框、登录按钮与找回密码链接，并在 `retranslateUi` 中设置多语言文本，`resizeEvent` 中保持背景图按比例填充。【F:qfluentwidgets/test/login_window.cpp†L3-L172】
- English: `LoginWindow` extends `AcrylicWindow`, building a split layout with a background image on the left and a full FTP login form on the right—host, port, username, password, remember checkbox, login button, and recovery link—while `retranslateUi` handles localisation and `resizeEvent` keeps the background scaled.【F:qfluentwidgets/test/login_window.cpp†L3-L172】
- 运行 Run：可在自定义项目中直接实例化 `LoginWindow` 并调用 `show()`；此演示未在 CMake 中注册独立目标，可根据需要手动添加。【F:CmakeLists.txt†L40-L1432】

## Media Player (`media_player_test.cpp`)
- 中文：`MediaPlayerView1` 同时展示简洁与标准播放条并加载远程音频，`MediaPlayerView2` 通过 `VideoWidget` 播放视频，验证多媒体组件的源设置与播放控制。【F:qfluentwidgets/test/media_player_test.cpp†L15-L80】
- English: `MediaPlayerView1` compares the simple and standard media play bars with remote audio sources, while `MediaPlayerView2` plays video via `VideoWidget`, exercising media source configuration and playback control.【F:qfluentwidgets/test/media_player_test.cpp†L15-L80】
- 运行 Run：`cmake --build build --target media_player_test && ./build/media_player_test`。【F:CmakeLists.txt†L552-L574】

## Menu (`menu_test.cpp`)
- 中文：`Demo` 在右键时弹出 `RoundMenu`，包含图标动作、子菜单、快捷键、插入位置与复选项等配置；`Demo1` 则使用 `CheckableMenu` 展示单选/多选指示器与动作分组，覆盖 Fluent 菜单的主要特性。【F:qfluentwidgets/test/menu_test.cpp†L15-L200】
- English: `Demo` opens a `RoundMenu` on right-click with icon actions, nested menus, shortcuts, insertion points, and checkable items, while `Demo1` leverages `CheckableMenu` to demonstrate radio-style indicators and action grouping, covering key Fluent menu features.【F:qfluentwidgets/test/menu_test.cpp†L15-L200】
- 运行 Run：`cmake --build build --target menu_test && ./build/menu_test`。【F:CmakeLists.txt†L604-L627】

## Message Dialog (`message_dialog_test.cpp`)
- 中文：`MessageDialogDemo` 调用 `MessageBoxF` 显示确认删除提示，并依据返回值记录用户选择，是 Fluent 消息框的基础用法示例。【F:qfluentwidgets/test/message_dialog_test.cpp†L17-L58】
- English: `MessageDialogDemo` launches `MessageBoxF` to confirm folder deletion and logs the chosen button, illustrating the basic Fluent message dialog workflow.【F:qfluentwidgets/test/message_dialog_test.cpp†L17-L58】
- 运行 Run：`cmake --build build --target message_dialog_test && ./build/message_dialog_test`。【F:CmakeLists.txt†L383-L403】

## Navigation (Panel) I (`navigation1_test.cpp`)
- 中文：`Window` 基于 `NavigationInterface` 组织多层级页面，包含顶部搜索/媒体项、滚动区专辑与文件夹、底部头像和设置，并同步 `QStackedWidget` 与导航项状态，展示分组、子项与自定义小部件等能力。【F:qfluentwidgets/test/navigation1_test.cpp†L23-L205】
- English: `Window` wires a `NavigationInterface` to a `QStackedWidget`, adding top-level search/media entries, scrollable album hierarchies, and bottom avatar/settings items while keeping the current item in sync—showcasing grouping, nested pages, and custom widgets inside the navigation panel.【F:qfluentwidgets/test/navigation1_test.cpp†L23-L205】
- 运行 Run：`cmake --build build --target navigation1_test && ./build/navigation1_test`。【F:CmakeLists.txt†L972-L994】

## Navigation (Compact) II (`navigation2_test.cpp`)
- 中文：示例定制 `NavigationWidget` 以绘制头像和文本，并自定义 `TitleBar` 插入图标与标题标签；导航项支持紧凑模式、底部自定义头像按钮以及路由同步，展示标题栏与导航的协同布局。【F:qfluentwidgets/test/navigation2_test.cpp†L23-L270】
- English: This sample customises `NavigationWidget` to render an avatar and label, injects icon/title labels into a bespoke `TitleBar`, and wires compact navigation with a bottom avatar button plus router synchronisation, highlighting coordinated layout between the title bar and navigation.【F:qfluentwidgets/test/navigation2_test.cpp†L23-L270】
- 运行 Run：`cmake --build build --target navigation2_test && ./build/navigation2_test`。【F:CmakeLists.txt†L998-L1020】

## Navigation (Top App Bar) III (`navigation3_test.cpp`)
- 中文：自定义 `NavigationBar2` 将汉堡按钮与 `NavigationPanel` 结合，实现顶部应用栏呼出左侧导航抽屉，并在 `Window` 中同步 `QStackedWidget` 的当前页与标题，演示导航抽屉模式。【F:qfluentwidgets/test/navigation3_test.cpp†L41-L265】
- English: `NavigationBar2` integrates a hamburger button with `NavigationPanel`, expanding a left drawer from the top app bar and updating the title when routes change; `Window` hooks it to a `QStackedWidget` to demonstrate the drawer-style navigation experience.【F:qfluentwidgets/test/navigation3_test.cpp†L41-L265】
- 运行 Run：`cmake --build build --target navigation3_test && ./build/navigation3_test`。【F:CmakeLists.txt†L946-L968】

## Navigation Bar (`navigation_bar_test.cpp`)
- 中文：通过自定义 `CustomTitleBar` 集成搜索框与窗口按钮，配合 `NavigationBar` 和带动画的 `MStackedWidget`，实现底部标签栏切换不同内容页，支持图标切换、过渡动画与标题更新。【F:qfluentwidgets/test/navigation_bar_test.cpp†L26-L302】
- English: The sample embeds a search bar and caption buttons in `CustomTitleBar`, then pairs `NavigationBar` with an animated `MStackedWidget` to switch bottom tabs with icon states, transitions, and title updates for each content page.【F:qfluentwidgets/test/navigation_bar_test.cpp†L26-L302】
- 运行 Run：`cmake --build build --target navigation_bar_test && ./build/navigation_bar_test`。【F:CmakeLists.txt†L1024-L1047】

## Pips Pager (`pips_pager_test.cpp`)
- 中文：水平与垂直 `PipsPager` 并列展示，设置页面数量、可见分页数以及滚动按钮的显示模式，演示分页指示器的配置选项。【F:qfluentwidgets/test/pips_pager_test.cpp†L11-L36】
- English: The demo places horizontal and vertical `PipsPager` widgets side by side, adjusting page count, visible range, and scroll button policies to illustrate pager configuration.【F:qfluentwidgets/test/pips_pager_test.cpp†L11-L36】
- 运行 Run：`cmake --build build --target pips_pager_test && ./build/pips_pager_test`。【F:CmakeLists.txt†L1286-L1308】

## Pivot (`pivot_test.cpp`)
- 中文：`Pivot` 与 `QStackedWidget` 同步切换“Song/Album/Artist”三个页面，演示如何注册项并在切换时更新当前选中状态。【F:qfluentwidgets/test/pivot_test.cpp†L11-L58】
- English: The demo links a `Pivot` to a `QStackedWidget`, wiring callbacks so selecting “Song/Album/Artist” updates both the stack and the active pivot item.【F:qfluentwidgets/test/pivot_test.cpp†L11-L58】
- 运行 Run：`cmake --build build --target pivot_test && ./build/pivot_test`。【F:CmakeLists.txt†L1052-L1074】

## Progress Bar (`progress_bar_test.cpp`)
- 中文：同步展示确定与不确定两种进度条，并通过切换按钮控制暂停/恢复，同时切换按钮图标，演示动画控制接口。【F:qfluentwidgets/test/progress_bar_test.cpp†L14-L60】
- English: The demo shows both determinate and indeterminate progress bars, toggled by a button that pauses/resumes the animations and swaps icons, highlighting control APIs.【F:qfluentwidgets/test/progress_bar_test.cpp†L14-L60】
- 运行 Run：`cmake --build build --target progress_bar_test && ./build/progress_bar_test`。【F:CmakeLists.txt†L761-L783】

## Progress Ring (`progress_ring_test.cpp`)
- 中文：`ProgressRing` 与 `SpinBox` 绑定实时更新百分比，另配不确定环形动画，并通过按钮切换暂停/恢复，展示文本显示与尺寸设置。【F:qfluentwidgets/test/progress_ring_test.cpp†L15-L72】
- English: The demo ties a `ProgressRing` to a `SpinBox` for live percentage updates, includes an indeterminate ring, and uses a toggle button to pause/resume while changing icons, demonstrating text display and sizing.【F:qfluentwidgets/test/progress_ring_test.cpp†L15-L72】
- 运行 Run：`cmake --build build --target progress_ring_test && ./build/progress_ring_test`。【F:CmakeLists.txt†L787-L809】

## Radio Button (`radio_button_test.cpp`)
- 中文：将三个 `RadioButton` 横向排列，便于测试互斥选择与主题样式效果。【F:qfluentwidgets/test/radio_button_test.cpp†L15-L56】
- English: Three `RadioButton` controls are arranged horizontally to observe mutual exclusivity and theming.【F:qfluentwidgets/test/radio_button_test.cpp†L15-L56】
- 运行 Run：`cmake --build build --target radio_button_test && ./build/radio_button_test`。【F:CmakeLists.txt†L142-L174】

## Scroll Area (`scroll_area_test.cpp`)
- 中文：`SmoothScrollArea` 加载大尺寸图片，启用水平/垂直平滑滚动动画并套用自定义样式，展示改良滚动体验。【F:qfluentwidgets/test/scroll_area_test.cpp†L9-L33】
- English: `SmoothScrollArea` hosts a large pixmap, enables animated scrolling on both axes, and applies a custom stylesheet to showcase enhanced scroll interactions.【F:qfluentwidgets/test/scroll_area_test.cpp†L9-L33】
- 运行 Run：`cmake --build build --target scroll_area_test && ./build/scroll_area_test`。【F:CmakeLists.txt†L1312-L1334】

## Segmented Toggle Tool Widget (`segmented_tool_widget_test.cpp`)
- 中文：`SegmentedToggleToolWidget` 搭配 `QStackedWidget` 提供图标化的分段切换，三个标签页分别显示 Song/Album/Artist，并保持当前项同步。【F:qfluentwidgets/test/segmented_tool_widget_test.cpp†L14-L79】
- English: The segmented toggle tool widget drives a `QStackedWidget` through iconised segments for Song/Album/Artist, keeping the current item aligned between the pivot and stack.【F:qfluentwidgets/test/segmented_tool_widget_test.cpp†L14-L79】
- 运行 Run：`cmake --build build --target segmented_tool_widget_test && ./build/segmented_tool_widget_test`。【F:CmakeLists.txt†L1078-L1101】

## Segmented Widget (`segmented_widget_test.cpp`)
- 中文：`SegmentedWidget` 使用文本标签构成分段器，与 `QStackedWidget` 联动切换 Song/Album/Artist 页面，与工具版示例形成对比。【F:qfluentwidgets/test/segmented_widget_test.cpp†L14-L76】
- English: The text-based `SegmentedWidget` drives a `QStackedWidget` across Song/Album/Artist pages, mirroring the tool-button variant for comparison.【F:qfluentwidgets/test/segmented_widget_test.cpp†L14-L76】
- 运行 Run：`cmake --build build --target segmented_widget_test && ./build/segmented_widget_test`。【F:CmakeLists.txt†L1105-L1127】

## Settings Interface (`setting_test.cpp` 与 `settings_test/`)
- 中文：`setting_test.cpp` 初始化翻译、读取配置并在无边框窗口中加载 `SettingInterface`，后者通过 `ExpandLayout` 组织在线音乐、个性化和关于等分组，包含范围设置、选项、开关、下拉、超链接卡片，并在主题或语言变更时触发提示。【F:qfluentwidgets/test/setting_test.cpp†L16-L90】【F:qfluentwidgets/test/settings_test/setting_interface.cpp†L4-L200】
- English: `setting_test.cpp` sets up translators, reads configuration, and embeds `SettingInterface` inside a frameless window. The interface arranges groups such as Online Music, Personalisation, and About via `ExpandLayout`, mixing range, option, switch, combo box, hyperlink, and primary action cards while showing restart tooltips when settings change.【F:qfluentwidgets/test/setting_test.cpp†L16-L90】【F:qfluentwidgets/test/settings_test/setting_interface.cpp†L4-L200】
- 运行 Run：`cmake --build build --target settings_test && ./build/settings_test`。【F:CmakeLists.txt†L1336-L1363】

## Slider (`slider_test.cpp`)
- 中文：`SliderDemo1` 为原生 `QSlider` 应用 `HollowHandleStyle` 自定义子轨道颜色，`SliderDemo2` 展示横向与纵向 `Slider` 组件，便于体验 Fluent 样式滑块。【F:qfluentwidgets/test/slider_test.cpp†L15-L83】
- English: `SliderDemo1` applies `HollowHandleStyle` to a native `QSlider` to recolour the sub-page, while `SliderDemo2` shows horizontal and vertical Fluent `Slider` widgets for styling comparison.【F:qfluentwidgets/test/slider_test.cpp†L15-L83】
- 运行 Run：`cmake --build build --target slider_test && ./build/slider_test`。【F:CmakeLists.txt†L176-L198】

## Spin & Date/Time Boxes (`spin_box_test.cpp`)
- 中文：示例构建网格布局，成对展示标准与紧凑版的数值、浮点、时间、日期、日期时间编辑器，并启用加速输入，便于比较不同形态。【F:qfluentwidgets/test/spin_box_test.cpp†L14-L69】
- English: The grid layout pairs standard and compact variants of numeric, double, time, date, and datetime editors with accelerated stepping, enabling side-by-side comparison.【F:qfluentwidgets/test/spin_box_test.cpp†L14-L69】
- 运行 Run：`cmake --build build --target spin_box_test && ./build/spin_box_test`。【F:CmakeLists.txt†L920-L942】

## State Tool Tip (`state_tool_tip_test.cpp`)
- 中文：按钮首次点击创建 `StateToolTip` 显示“正在训练”提示，再次点击更新内容并切换状态为完成，用于演示进度型提示的动态交互。【F:qfluentwidgets/test/state_tool_tip_test.cpp†L14-L37】
- English: The first click spawns a `StateToolTip` for “training in progress”, while the next click updates the message and marks it as finished, illustrating dynamic state tooltips.【F:qfluentwidgets/test/state_tool_tip_test.cpp†L14-L37】
- 运行 Run：`cmake --build build --target state_tool_tip_test && ./build/state_tool_tip_test`。【F:CmakeLists.txt†L813-L835】

## Tab View (`tab_view_test.cpp`)
- 中文：自定义 `CustomTitleBar` 将搜索、前进/后退按钮、头像与 `TabBar` 集成于窗体顶部，`Window` 继承 `MSFluentWindow` 使用 `TabView` 动态创建页面，演示 Fluent 风格的多标签导航与标题栏一体化设计。【F:qfluentwidgets/test/tab_view_test.cpp†L28-L265】
- English: `CustomTitleBar` embeds search, navigation buttons, an avatar, and a movable `TabBar` into the frame while `Window` (an `MSFluentWindow`) manages tabbed content via `TabView`, showcasing Fluent-style integrated tab navigation and title bar design.【F:qfluentwidgets/test/tab_view_test.cpp†L28-L265】
- 运行 Run：`cmake --build build --target tab_view_test && ./build/tab_view_test`。【F:CmakeLists.txt†L1131-L1153】

## Table View (`table_view_test.cpp`)
- 中文：`TableWidget` 设置显示边框与表头，填充大量歌曲元数据并调整行高、隐藏垂直表头，展示 Fluent 样式表格的滚动与内容布局。【F:qfluentwidgets/test/table_view_test.cpp†L16-L144】
- English: The demo populates a `TableWidget` with extensive song metadata, enabling borders, setting headers, and resizing rows to highlight Fluent-styled table presentation.【F:qfluentwidgets/test/table_view_test.cpp†L16-L144】
- 运行 Run：`cmake --build build --target table_view_test && ./build/table_view_test`。【F:CmakeLists.txt†L1234-L1256】

## Teaching Tip (`teaching_tip_test.cpp`)
- 中文：三个按钮分别调用 `TeachingTipView`、静态 `TeachingTip::create` 与 `PopupTeachingTip::make`，演示尾部位置、附加操作按钮以及自定义视图的教学提示用法。【F:qfluentwidgets/test/teaching_tip_test.cpp†L9-L95】
- English: The buttons trigger `TeachingTipView`, the static `TeachingTip::create`, and `PopupTeachingTip::make`, covering tail positioning, extra action buttons, and custom view content for teaching tips.【F:qfluentwidgets/test/teaching_tip_test.cpp†L9-L95】
- 运行 Run：`cmake --build build --target teaching_tip_test && ./build/teaching_tip_test`。【F:CmakeLists.txt†L406-L426】

## Scroll Area 基础示例 (`test.cpp`)
- 中文：主函数直接创建 `ScrollArea` 并填充 100 个标签，演示最基本的滚动区域用法与自动调整大小设置。【F:qfluentwidgets/test/test.cpp†L13-L37】
- English: The standalone `main` builds a `ScrollArea`, fills it with 100 labels, and enables widget resizing to demonstrate the simplest scrolling setup.【F:qfluentwidgets/test/test.cpp†L13-L37】
- 运行 Run：`cmake --build build --target test && ./build/test`。【F:CmakeLists.txt†L1373-L1395】

## Date & Time Pickers (`time_picker_test.cpp`)
- 中文：示例同时展示美式日期、中文日期以及 12/24 小时制时间选择器，并为秒列设置自定义格式化器，演示 `PickerBase` 的扩展能力。【F:qfluentwidgets/test/time_picker_test.cpp†L11-L64】
- English: The demo combines US and Chinese date pickers with AM/PM and 24-hour time pickers, applying a custom formatter to the seconds column to illustrate `PickerBase` extensibility.【F:qfluentwidgets/test/time_picker_test.cpp†L11-L64】
- 运行 Run：`cmake --build build --target time_picker_test && ./build/time_picker_test`。【F:CmakeLists.txt†L224-L248】

## Tool Tip (`tool_tip_test.cpp`)
- 中文：三个按钮分别安装不同位置与延迟的 `ToolTipFilter` 并设置自定义提示文本，演示 Fluent 工具提示的定位与持续时间控制。【F:qfluentwidgets/test/tool_tip_test.cpp†L15-L43】
- English: The demo installs `ToolTipFilter` instances with varying positions and delays on three buttons, each with custom tooltip text, showcasing Fluent tooltip positioning and duration control.【F:qfluentwidgets/test/tool_tip_test.cpp†L15-L43】
- 运行 Run：`cmake --build build --target tool_tip_test && ./build/tool_tip_test`。【F:CmakeLists.txt†L839-L861】

## Tree View (`tree_view_test.cpp`)
- 中文：`TreeView` 绑定 `QFileSystemModel` 浏览当前目录，并启用边框与圆角，展示 Fluent 树视图与文件系统模型结合的样式。【F:qfluentwidgets/test/tree_view_test.cpp†L11-L36】
- English: The demo connects a `TreeView` to a `QFileSystemModel` rooted at the current directory, enabling borders and rounded corners to highlight Fluent-styled tree navigation.【F:qfluentwidgets/test/tree_view_test.cpp†L11-L36】
- 运行 Run：`cmake --build build --target tree_view_test && ./build/tree_view_test`。【F:CmakeLists.txt†L1260-L1282】

## Widget Menu (`widget_menu_test.cpp`)
- 中文：右键弹出的 `RoundMenu` 首先插入自定义 `ProfileCard`，再附加多项带图标的动作，展示菜单中混合自定义部件与标准操作的能力。【F:qfluentwidgets/test/widget_menu_test.cpp†L18-L116】
- English: Right-clicking opens a `RoundMenu` that hosts a custom `ProfileCard` widget before adding icon-backed actions, highlighting how menus can mix bespoke content with regular items.【F:qfluentwidgets/test/widget_menu_test.cpp†L18-L116】
- 运行 Run：`cmake --build build --target widget_menu_test && ./build/widget_menu_test`。【F:CmakeLists.txt†L658-L680】
