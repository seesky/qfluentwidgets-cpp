# qfluentwidgets-cpp

qt widgets lib for c++. This code is used for Poleis.Poleis is a remote desktop app in developping.

## 编译环境准备（MinGW）

以下步骤以 **Qt 5.15.2 + MinGW-w64 8.1.0 (64-bit)** 为例，其它版本亦可，需确保 Qt、MinGW 和 CMake 版本匹配。

1. **安装 Qt**
   - 使用 Qt 在线安装器，勾选 *Qt 5.15.2 -> Mingw 8.1.0 64-bit* 组件。
   - 记录 Qt 安装目录，例如：`C:\Qt\5.15.2\mingw81_64`。

2. **安装 MinGW-w64 工具链**
   - 推荐使用 Qt 随附的 MinGW，路径位于 `C:\Qt\Tools\mingw810_64`。
   - 将 `<Qt安装目录>\Tools\mingw810_64\bin` 添加至 `PATH` 环境变量。

3. **安装 CMake（>=3.16）**
   - 可通过 [cmake.org](https://cmake.org/download/) 下载 Windows 安装包。
   - 将 CMake 安装路径加入 `PATH`。

4. **安装 Ninja（可选）**
   - 若希望使用 Ninja 进行多核并行编译，可从 [ninja-build.org](https://github.com/ninja-build/ninja/releases) 下载，可执行文件需加入 `PATH`。

5. **准备第三方依赖**
   - 项目依赖 `jsoncpp`，MinGW 版本 Qt 常自带该库。若 CMake 未找到，可使用 [vcpkg](https://github.com/microsoft/vcpkg) 或自行编译并在配置阶段通过 `-DJSONCPP_ROOT=<路径>` 指定安装目录。

## 配置与编译步骤

> 以下命令需在 **Qt 命令行环境** 中执行，确保所有 Qt/MinGW 工具位于 `PATH`。

1. **获取源码**

   ```powershell
   git clone https://github.com/<your-account>/qfluentwidgets-cpp.git
   cd qfluentwidgets-cpp
   ```

2. **创建构建目录**

   ```powershell
   mkdir build
   cd build
   ```

3. **配置工程**

   - 使用 MinGW Makefiles 生成器：

     ```powershell
     cmake ^
       -G "MinGW Makefiles" ^
       -DCMAKE_BUILD_TYPE=Release ^
       -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/mingw81_64" ^
       ..
     ```

   - 若使用 Ninja：

     ```powershell
     cmake ^
       -G Ninja ^
       -DCMAKE_BUILD_TYPE=Release ^
       -DCMAKE_C_COMPILER=clang.exe ^
       -DCMAKE_CXX_COMPILER=clang++.exe ^
       -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/mingw81_64" ^
       ..
     ```

     > 注：若仍使用 MinGW 的 `gcc/g++`，可省略 `-DCMAKE_C_COMPILER` 与 `-DCMAKE_CXX_COMPILER` 参数。

4. **开始编译**

   ```powershell
   cmake --build . --target gallery --config Release
   ```

   上述命令以构建 `gallery` 示例程序为例；若需要构建所有测试，可省略 `--target` 参数。

5. **运行示例**

   ```powershell
   ./gallery.exe
   ```

## 常见问题

- **找不到 Qt5::Widgets 等库**：
  - 确认 `CMAKE_PREFIX_PATH` 指向 `Qt\<版本>\mingwXX_YY` 根目录。
  - 若使用 Qt6，请调整 `CMAKE_PREFIX_PATH` 并启用相应的 Qt6 模块。

- **找不到 jsoncpp**：
  - 确认 Qt 安装目录下的 `lib/cmake/jsoncpp` 已添加到 `CMAKE_PREFIX_PATH`。
  - 手动安装 jsoncpp 后，通过 `-DJSONCPP_ROOT=<安装路径>` 提供线索。

- **中文路径导致编码问题**：
  - 建议将仓库及 Qt 安装位置放在纯英文路径下，例如 `C:\dev\`。

## reference

If you use it commercially, please support the original author.

https://github.com/zhiyiYo/PyQt-Fluent-Widgets.git
