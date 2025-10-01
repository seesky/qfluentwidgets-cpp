# Components Usage Guide / 组件使用指南

> This guide summarises every component provided under `qfluentwidgets/components`. Each subsection first provides an English usage note followed by a Chinese translation so that you can quickly integrate the widgets into your Qt application.
>
> 本指南汇总了 `qfluentwidgets/components` 目录下的全部组件。每个小节先给出英文使用说明，再提供中文翻译，方便在 Qt 应用中快速集成这些控件。

## Date & Time Components / 日期与时间组件

### CalendarPicker & CalendarView
- **English**: `CalendarPicker` wraps a push button that opens a `CalendarView` pop-up. Use `setDate(const QDate&)`, `setDateFormat(QVariant*)`, and the `dateChanged(QDate)` signal to integrate with your data model. The `CalendarView` manages year, month, and day views with smooth scrolling (`YearScrollView`, `MonthScrollView`, `DayScrollView`) and emits `dateChanged(QDate)` when the selection updates. Customize animations and shadow effects through `setShadowEffect()` and use `_on*` slots to navigate between stacked views.
- **中文**：`CalendarPicker` 是一个按钮，点击后会弹出 `CalendarView`。可以通过 `setDate(const QDate&)`、`setDateFormat(QVariant*)` 设置日期格式，并监听 `dateChanged(QDate)` 信号与数据模型同步。`CalendarView` 内部包含年、月、日三种视图（`YearScrollView`、`MonthScrollView`、`DayScrollView`），并在选择变化时发出 `dateChanged(QDate)` 信号。可调用 `setShadowEffect()` 调整阴影，或使用 `_on*` 槽函数在堆叠视图之间切换。

### PickerBase Framework
- **English**: `PickerBase` provides a multi-column popup selector using `PickerPanel`. Add columns with `addColumn(...)`, customise alignment/formatters via `setColumnAlignment`, `setColumnFormatter`, and react to selections through `_onConfirmed(QList<QString>*)`. Use `PickerPanel::exec()` to display the panel with optional animations, and `PickerColumnFormatter` (including `DigitFormatter`) to convert between textual values and typed data.
- **中文**：`PickerBase` 通过 `PickerPanel` 提供多列选择面板。可调用 `addColumn(...)` 添加列，通过 `setColumnAlignment`、`setColumnFormatter` 自定义对齐和格式化，并在 `_onConfirmed(QList<QString>*)` 中处理最终结果。利用 `PickerPanel::exec()` 显示弹窗并可配合动画，`PickerColumnFormatter`（如 `DigitFormatter`）用于在文本和真实数据之间转换。

### Date Picker Family
- **English**: `DatePickerBase` stores the selected `QDate` and exposes `setYearFormatter`, `setMonthFormatter`, `setDayFormatter` hooks. `DatePicker` adds column management for various formats (`MM_DD_YYYY`, `YYYY_MM_DD`) and emits `dateChanged(QDate)`. `ZhDatePicker` ships with localized formatters (`ZhYearFormatter`, etc.) for Chinese labels. Use `setMonthTight()` to control column spacing.
- **中文**：`DatePickerBase` 负责维护所选 `QDate`，并提供 `setYearFormatter`、`setMonthFormatter`、`setDayFormatter` 接口供自定义格式。`DatePicker` 支持不同格式（`MM_DD_YYYY`、`YYYY_MM_DD`），并在日期改变时发出 `dateChanged(QDate)`。`ZhDatePicker` 内置 `ZhYearFormatter` 等中文格式化器，用于显示中文年月日单位；可通过 `setMonthTight()` 控制列间距。

### Time Picker Series
- **English**: `TimePickerBase` tracks a `QTime` with optional seconds. `TimePicker` provides a 24-hour picker, while `AMTimePicker` formats values into AM/PM columns using `AMPMFormatter`. Use `setSecondVisible(bool)` to toggle the seconds column and listen to `timeChanged(QTime)` for updates.
- **中文**：`TimePickerBase` 管理 `QTime`，可选显示秒数。`TimePicker` 提供 24 小时制选择，`AMTimePicker` 则使用 `AMPMFormatter` 提供 AM/PM 列。通过 `setSecondVisible(bool)` 控制秒列是否显示，并监听 `timeChanged(QTime)` 获取变化。

## Dialog Box Components / 对话框组件

### MaskDialogBase & Dialog
- **English**: `MaskDialogBase` is the frameless foundation for masked dialogs. Configure appearance using `setShadowEffect(...)` and `setMaskColor(...)`; override `eventFilter` to intercept keyboard/mouse events. `Dialog` builds on a frameless window with title/content labels, exposes `yesSignal` and `cancelSignal`, and supports `setContentCopyable` plus optional title bar visibility.
- **中文**：`MaskDialogBase` 是所有遮罩对话框的基础，提供无边框外观。可通过 `setShadowEffect(...)`、`setMaskColor(...)` 设置效果，并重写 `eventFilter` 拦截键鼠事件。`Dialog` 基于无边框窗口，拥有标题和正文标签，提供 `yesSignal`、`cancelSignal`，支持 `setContentCopyable` 以及可选标题栏显示。

### Message Dialog Variants
- **English**: `MessageBoxBase` supplies shared layout and `accepted/rejected` signals for message dialogs. `MessageBoxF` and `MessageDialog` specialise the base with auto-wrapping content, confirm/cancel buttons, and copyable text. Connect to their `yesSignal`/`cancelSignal` slots to handle user decisions.
- **中文**：`MessageBoxBase` 为消息类对话框提供通用布局及 `accepted/rejected` 信号。`MessageBoxF` 与 `MessageDialog` 在此基础上增加自动换行文本、确认/取消按钮以及可复制内容。可通过 `yesSignal`、`cancelSignal` 槽函数处理用户选择。

### Color Dialog
- **English**: `ColorDialog` offers HSV picking with alpha support. Combine `HuePanel`, `BrightnessSlider`, and channel-specific `ColorLineEdit` derivatives to read/write color components. Use `setColor(QColor,bool)` to sync UI and handle updates via `colorChanged(QColor)`.
- **中文**：`ColorDialog` 提供带透明度的 HSV 取色器，由 `HuePanel`、`BrightnessSlider` 及各类通道输入框组成。通过 `setColor(QColor,bool)` 同步界面，并监听 `colorChanged(QColor)` 获取颜色变化。

### FolderListDialog
- **English**: `FolderListDialog` manages a scrollable list of user-selected folders with removable `FolderCard` entries and an `AddFolderCard` trigger. Use the `folderChanged(QStringList)` signal to react when the list is confirmed or modified.
- **中文**：`FolderListDialog` 用于管理用户选择的文件夹列表，内部包含可删除的 `FolderCard` 项和用于新增的 `AddFolderCard`。通过 `folderChanged(QStringList)` 信号获取用户确认后的目录列表。

## Layout Components / 布局组件

### ExpandLayout
- **English**: `ExpandLayout` arranges child widgets horizontally or vertically while letting each widget expand. Call `addWidget` or `addItem` and the layout automatically recalculates geometry in `setGeometry`. Height-for-width behaviour (`hasHeightForWidth`) ensures responsive resizing.
- **中文**：`ExpandLayout` 负责在保留扩展空间的同时排列子控件。通过 `addWidget` 或 `addItem` 添加项目，布局会在 `setGeometry` 中自动重新计算；其 `hasHeightForWidth` 支持在横向宽度变化时调整高度。

### FlowLayout
- **English**: `FlowLayout` lays out items in rows with optional animations (`setAnimation`). Control spacing via `setVerticalSpacing`/`setHorizontalSpacing`, and use `removeAllWidgets`/`takeAllWidgets` for dynamic content.
- **中文**：`FlowLayout` 以流式方式排列子项，可通过 `setAnimation` 启用动画。使用 `setVerticalSpacing`、`setHorizontalSpacing` 控制间距，`removeAllWidgets`、`takeAllWidgets` 可在运行时批量更新内容。

### VBoxLayout Utility
- **English**: `VBoxLayout` extends Qt’s layout with helper methods `addWidgets`, `removeAllWidget`, and tracking of registered child widgets for easier cleanup.
- **中文**：`VBoxLayout` 在 Qt 标准纵向布局基础上增加 `addWidgets`、`removeAllWidget` 等便捷方法，并记录子控件列表以便统一管理。

## Material Components / 亚克力材质组件

### Acrylic Brush & Labels
- **English**: `AcrylicLabel`, `AcrylicTextureLabel`, and `AcrylicBrush` encapsulate Fluent Design acrylic effects. Use `AcrylicBrush::grabImage()` with `setClipPath()` to render blurred backgrounds; `AcrylicLabel` updates blur asynchronously through `BlurCoverThread`.
- **中文**：`AcrylicLabel`、`AcrylicTextureLabel` 与 `AcrylicBrush` 封装 Fluent 亚克力效果。通过 `AcrylicBrush::grabImage()` 结合 `setClipPath()` 渲染模糊背景，`AcrylicLabel` 则借助 `BlurCoverThread` 异步更新模糊图像。

### AcrylicFlyout
- **English**: `AcrylicFlyoutViewBase` and `AcrylicFlyoutView` draw acrylic backgrounds for flyout panels. Use the factory helpers `AcrylicFlyout::create` and `make` to spawn flyouts with `FlyoutAnimationType` transitions, and override `_drawAcrylic` when custom painting is required.
- **中文**：`AcrylicFlyoutViewBase` 与 `AcrylicFlyoutView` 为飞出面板绘制亚克力背景。可使用 `AcrylicFlyout::create`、`make` 快速生成带 `FlyoutAnimationType` 动画的飞出窗，如需自定义绘制可重写 `_drawAcrylic`。

### Acrylic Line Edit & Menu
- **English**: `AcrylicLineEdit`/`AcrylicSearchLineEdit` override context menus to show acrylic-styled completions. Pair them with `AcrylicMenu`, `AcrylicCompleterMenu`, or `AcrylicLineEditMenu` for consistent blurred menus.
- **中文**：`AcrylicLineEdit`、`AcrylicSearchLineEdit` 重写上下文菜单以展示亚克力风格的补全框。可与 `AcrylicMenu`、`AcrylicCompleterMenu`、`AcrylicLineEditMenu` 搭配使用，获得统一的模糊菜单效果。

## Navigation Components / 导航组件

### NavigationWidget Hierarchy
- **English**: `NavigationWidget` manages shared hover/press/selection states. `NavigationPushButton`, `NavigationToolButton`, and `NavigationTreeWidget` add icons, hierarchical expansion, and selection handling. Use `setCompacted(bool)` when toggling between expanded and minimal navigation modes.
- **中文**：`NavigationWidget` 负责处理悬停、按压、选中等通用状态；`NavigationPushButton`、`NavigationToolButton`、`NavigationTreeWidget` 则在此基础上增加图标、层级展开及选中逻辑。在导航面板展开/收起时可调用 `setCompacted(bool)` 调整表现。

### NavigationPanel & NavigationInterface
- **English**: `NavigationPanel` orchestrates navigation items, supports acrylic backgrounds, and exposes display modes (`NavigationDisplayMode`). Register routes through `addItem/addWidget`, manage separators, and control collapsible behaviour via `setCollapsible` and `expand/collapse`. `NavigationInterface` wraps the panel with optional menu/return buttons and re-emits `displayModeChanged`.
- **中文**：`NavigationPanel` 负责组织导航项，支持亚克力背景，并提供多种显示模式（`NavigationDisplayMode`）。可通过 `addItem/addWidget` 注册路由，使用 `addSeparator` 管理分隔符，并通过 `setCollapsible`、`expand/collapse` 控制折叠。`NavigationInterface` 在面板外层增加菜单/返回按钮，可转发 `displayModeChanged` 信号。

### NavigationBar & Breadcrumbs
- **English**: `NavigationBar` builds a vertical navigation list using `NavigationBarPushButton`, offering top/bottom sections and history integration. Use `setSelectedTextVisible` and `setCurrentItem` to manage selection. `BreadcrumbBar` maintains page hierarchies with `addItem`, `setCurrentItem`, and an overflow `ElideButton` menu.
- **中文**：`NavigationBar` 使用 `NavigationBarPushButton` 构建垂直导航列表，支持顶部/底部分区及路由历史。可调用 `setSelectedTextVisible`、`setCurrentItem` 控制选中状态。`BreadcrumbBar` 维护页面层级，提供 `addItem`、`setCurrentItem` 等方法，并通过 `ElideButton` 弹出隐藏项菜单。

### Pivot & Segmented Widgets
- **English**: `Pivot` arranges tab-like `PivotItem`s with slide animation (`FluentAnimation`). `SegmentedWidget`, `SegmentedToolWidget`, and `SegmentedToggleToolWidget` extend this pattern for segmented controls, exposing `addItem`, `setCurrentItem`, and selection toggles for tool buttons.
- **中文**：`Pivot` 使用 `PivotItem` 构建类似选项卡的导航，并配合 `FluentAnimation` 实现滑动指示。`SegmentedWidget`、`SegmentedToolWidget`、`SegmentedToggleToolWidget` 在此基础上实现分段控制条，提供 `addItem`、`setCurrentItem` 等接口以及工具按钮选中切换。

### Additional Navigation Utilities
- **English**: `NavigationBar`, `NavigationPanel`, and `NavigationFlyoutMenu` integrate with `Router` for history. Use tool-tip filters (`NavigationToolTipFilter`) to customise delay and auto-show behaviour.
- **中文**：`NavigationBar`、`NavigationPanel` 与 `NavigationFlyoutMenu` 均可结合 `Router` 管理历史；`NavigationToolTipFilter` 可自定义工具提示延迟和显示条件。

## Settings Components / 设置组件

### SettingCard Family
- **English**: `SettingCard` is the base card with icon, title, and description. Derived cards include `SwitchSettingCard`, `RangeSettingCard`, `PushSettingCard`/`PrimaryPushSettingCard`, `HyperlinkCard`, and `ColorSettingCard`. Use `setValue(...)` overloads to keep UI in sync and subscribe to `checkedChanged`, `valueChanged`, or `colorChanged` signals.
- **中文**：`SettingCard` 提供带图标、标题、说明的基础卡片。衍生卡片包括 `SwitchSettingCard`、`RangeSettingCard`、`PushSettingCard`/`PrimaryPushSettingCard`、`HyperlinkCard` 与 `ColorSettingCard`。可通过各自的 `setValue(...)` 方法同步状态，并监听 `checkedChanged`、`valueChanged`、`colorChanged` 等信号。

### Expandable Setting Groups
- **English**: `ExpandSettingCard` wraps a scroll area with animated expansion (`ExpandButton`, `setExpand(bool)`). `ExpandGroupSettingCard` adds grouped child widgets, while `HeaderSettingCard` provides a header row with toggle button. Use `toggleExpand()` to respond to user interaction.
- **中文**：`ExpandSettingCard` 结合滚动区域和 `ExpandButton` 提供可展开/收起的设置面板，`setExpand(bool)` 可直接控制状态。`ExpandGroupSettingCard` 支持按组展示子控件，`HeaderSettingCard` 则在头部提供展开开关。通过 `toggleExpand()` 响应用户点击。

### Options, Folder, and Custom Color Settings
- **English**: `OptionsSettingCard` shows mutually exclusive `RadioButton` options and emits `optionChanged(OptionsConfigItem*)`. `FolderListSettingCard` collects folder paths via `__showFolderDialog()` and notifies through `folderChanged`. `CustomColorSettingCard` lets users choose between default/custom colors and opens `ColorDialog` when editing the custom option.
- **中文**：`OptionsSettingCard` 使用 `RadioButton` 呈现互斥选项，并通过 `optionChanged(OptionsConfigItem*)` 通知选择。`FolderListSettingCard` 借助 `__showFolderDialog()` 收集文件夹路径，并通过 `folderChanged` 反馈。`CustomColorSettingCard` 支持在默认/自定义颜色间切换，编辑自定义颜色时弹出 `ColorDialog`。

### SettingCardGroup
- **English**: `SettingCardGroup` organises multiple cards with `addSettingCard(s)` and automatically adjusts layout using `ExpandLayout`. Use `adjustSize()` after dynamic modifications.
- **中文**：`SettingCardGroup` 用于集中管理多张设置卡片，`addSettingCard(s)` 可批量添加，并利用 `ExpandLayout` 自动排版；动态修改后调用 `adjustSize()` 即可刷新布局。

## Widget Components / 通用控件组件

### Acrylic Utilities
- **English**: `AcrylicLabel` and `AcrylicBrush` (see Material section) are reused across widgets for fluent blur effects.
- **中文**：`AcrylicLabel` 与 `AcrylicBrush`（见亚克力材质部分）可在多个控件中复用以实现 Fluent 模糊效果。

### Buttons & Toggles
- **English**: `PushButton` extends `QPushButton` with icon handling and hover/press painting; derived variants include `PrimaryPushButton`, `TransparentPushButton`, `ToggleButton`, `HyperlinkButton`, and tool-button counterparts (`ToolButton`, `PrimaryToolButton`, `TransparentToolButton`, `ToggleToolButton`). Use `_postInit()` hooks for subclass styling and connect to standard Qt signals.
- **中文**：`PushButton` 在 `QPushButton` 基础上增强图标管理与悬停/按压绘制；其派生类包括 `PrimaryPushButton`、`TransparentPushButton`、`ToggleButton`、`HyperlinkButton`，以及工具按钮系列（`ToolButton`、`PrimaryToolButton`、`TransparentToolButton`、`ToggleToolButton`）。各派生类可重写 `_postInit()` 自定义样式，并使用 Qt 默认信号。

### Selection Widgets
- **English**: `CheckBox`, `RadioButton` (inside buttons header), and `SwitchButton` deliver Fluent-themed toggles. `ComboBox` and `EditableComboBox` provide dropdown selection with custom menus, while `CycleListWidget` powers looping lists for pickers.
- **中文**：`CheckBox`、按钮文件中的 `RadioButton` 以及 `SwitchButton` 提供 Fluent 风格的开关控件。`ComboBox` 与 `EditableComboBox` 实现自定义下拉框，`CycleListWidget` 则用于日期/时间选择器中的循环列表。

### Text & Input Widgets
- **English**: `LineEdit`, `SearchLineEdit`, and `PasswordLineEdit` (see header) add clear buttons, suffix actions, and support for completers/menus. `SpinBox` and `Slider` families implement Fluent visuals with extended signals for dragging states. `Label` introduces color and weight helpers for typography.
- **中文**：`LineEdit`、`SearchLineEdit`、`PasswordLineEdit` 等输入框提供清除按钮、后缀动作以及补全/菜单支持。`SpinBox`、`Slider` 系列在 Fluent 外观下扩展了拖动状态信号，`Label` 则提供颜色和字重的便捷设置。

### Informational Widgets
- **English**: `InfoBadge`, `InfoBar`, and `StateToolTip` deliver badge notifications, stacked info bars, and contextual tips. `ProgressBar`, `ProgressRing`, and `ProgressCard` components render progress feedback, while `TeachingTip` supplies anchored help pop-ups with optional dismiss buttons.
- **中文**：`InfoBadge`、`InfoBar`、`StateToolTip` 用于徽标通知、堆叠信息条以及上下文提示。`ProgressBar`、`ProgressRing`、`ProgressCard` 系列用于展示进度反馈，`TeachingTip` 则提供带锚点的帮助弹窗，并支持添加关闭按钮。

### Navigation Helpers
- **English**: `Flyout`, `FlyoutView`, and `NavigationFlyoutMenu` (see navigation section) render contextual overlays. `PipsPager`, `TabView`, and `TableView` manage multi-page or table interfaces, with `StackedWidget` extending Qt’s stacked container with transitions.
- **中文**：`Flyout`、`FlyoutView`、`NavigationFlyoutMenu`（参见导航部分）用于绘制上下文覆盖层。`PipsPager`、`TabView`、`TableView` 管理多页或表格界面，`StackedWidget` 在 Qt 堆叠窗口基础上增加过渡动画。

### Lists, Views, and Scrolling
- **English**: `ListView`, `TreeView`, and `TableView` customise Qt item views with smooth scroll bars (`SmoothScrollBar`), while `ScrollArea` and `SingleDirectionScrollArea` tune scrolling behaviour and content alignment. Pair them with `ScrollButton`/`ScrollBar` for consistent styling.
- **中文**：`ListView`、`TreeView`、`TableView` 在 Qt 项目视图基础上增加平滑滚动条（`SmoothScrollBar`），`ScrollArea` 与 `SingleDirectionScrollArea` 则调整滚动方向及内容对齐。可与 `ScrollButton`、`ScrollBar` 搭配实现统一外观。

### Menus & Command Interfaces
- **English**: `RoundMenu`, `SystemTrayMenu`, and `CheckableMenu` define Fluent menus. `CommandBar`/`CommandButton` host quick actions with overflow management and tool-tip filters, while `CommandBarView` embeds the layout inside a flyout.
- **中文**：`RoundMenu`、`SystemTrayMenu`、`CheckableMenu` 构建 Fluent 风格菜单。`CommandBar`、`CommandButton` 提供带溢出管理的快速操作区，并结合工具提示过滤器；`CommandBarView` 则将命令布局嵌入飞出面板。

### Miscellaneous Widgets
- **English**: `CardWidget` variants deliver clickable cards with elevation animation. `Separator` draws Fluent dividers, `ToolTip` customises tooltip timing/placement, and `ScrollArea`/`ScrollBar` manage smooth scrolling. `FlipView` and `ListView` variants supply animated content transitions.
- **中文**：`CardWidget` 系列提供带点击及悬浮动画的卡片。`Separator` 绘制 Fluent 分隔线，`ToolTip` 控制提示显示时机与位置，`ScrollArea`、`ScrollBar` 实现平滑滚动。`FlipView`、`ListView` 等组件可呈现带动画的内容切换。

## Integration Tips / 集成提示

- **English**: All components rely on Qt Widgets; include the relevant headers under `qfluentwidgets/components/...` and ensure a QApplication instance applies Fluent styles via `StyleSheetHelper`. Most interactive widgets expose Qt signals—connect them to your controllers for state updates. When using acrylic components, verify `AcrylicBrush::isAvailable()` before enabling blur-intensive effects.
- **中文**：所有组件均基于 Qt Widgets 开发，使用时需包含 `qfluentwidgets/components/...` 下的相应头文件，并通过 `StyleSheetHelper` 为 QApplication 应用 Fluent 样式。多数交互式控件都提供 Qt 信号，可连接到业务逻辑更新状态。启用亚克力相关组件前，建议先检查 `AcrylicBrush::isAvailable()`，以免在不支持的环境中出现性能问题。
