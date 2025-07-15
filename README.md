# PlatformDirs

A single-header C++17+ library for retrieving cross-platform application directories such as config, cache, data, and log folders. Supports Windows, macOS, Linux, Android (via JNI), and iOS (via Foundation).


[![CI Ubuntu](https://github.com/NoahGWood/PlatformDirs/actions/workflows/test.yml/badge.svg?branch=main)](https://github.com/NoahGWood/PlatformDirs/actions/workflows/test.yml)
[![CI macOS](https://github.com/NoahGWood/PlatformDirs/actions/workflows/mactest.yml/badge.svg?branch=main)](https://github.com/NoahGWood/PlatformDirs/actions/workflows/mactest.yml)
[![CI Windows](https://github.com/NoahGWood/PlatformDirs/actions/workflows/wintest.yml/badge.svg?branch=main)](https://github.com/NoahGWood/PlatformDirs/actions/workflows/wintest.yml)


## Features

- Cross-platform: Windows, macOS, Linux, Android, iOS
- Clean `std::filesystem::path` API
- Header-only, zero external dependencies
- Supports app-specific folder resolution
- JNI and Objective-C++ hooks for mobile

## Usage

```cpp
#include "platform_dirs.hpp"

auto config_path = platform_dirs::get_app_dir("MyApp");
```

### Android Setup

You **must call `platform_dirs::init()`** with the JNI context before using `get_app_dir()`:

```cpp
extern "C" JNIEXPORT void JNICALL
Java_com_example_MainActivity_init(JNIEnv* env, jobject ctx) {
    platform_dirs::init(env, ctx);
}
```

### iOS

Include the file in an Objective-C++ (`.mm`) file if using iOS.

## Utility Methods

- `get_app_dir(app_name)` 
- `get_config_dir(app_name)`
- `get_cache_dir(app_name)`
- `get_data_dir(app_name)`
- `get_log_dir(app_name)`
- `get_temp_dir()` (no app name needed)

## Design Notes

- Falls back to `$HOME/.config` or platform-specific conventions
- Uses `getenv()` for desktop env vars
- Android and iOS use system APIs via JNI and Foundation respectively
- Returns empty path or `/tmp` if fallback is needed

## Build

No build system needed — just include the header. For CMake:

```cmake
target_include_directories(your_target PRIVATE vendor/PlatformDirs/include)
```

## License

Licensed under GPLv3