#include <iostream>
#include "platform_dirs.hpp"

int main() {
    std::string app = "TestApp";

    std::cout << "App Dir:     " << PlatformDirs::get_app_dir(app) << "\n";
    std::cout << "Config Dir:  " << PlatformDirs::get_config_dir(app) << "\n";
    std::cout << "Cache Dir:   " << PlatformDirs::get_cache_dir(app) << "\n";
    std::cout << "Data Dir:    " << PlatformDirs::get_data_dir(app) << "\n";
    std::cout << "Log Dir:     " << PlatformDirs::get_log_dir(app) << "\n";
    std::cout << "Temp Dir:    " << PlatformDirs::get_temp_dir() << "\n";

    return 0;
}
