#include <iostream>
#include "platform_dirs.hpp"

int main() {
    std::string app = "TestApp";

    std::cout << "App Dir:     " << std::filesystem::get_app_dir(app) << "\n";
    std::cout << "Config Dir:  " << std::filesystem::get_config_dir(app) << "\n";
    std::cout << "Cache Dir:   " << std::filesystem::get_cache_dir(app) << "\n";
    std::cout << "Data Dir:    " << std::filesystem::get_data_dir(app) << "\n";
    std::cout << "Log Dir:     " << std::filesystem::get_log_dir(app) << "\n";
    std::cout << "Temp Dir:    " << std::filesystem::get_temp_dir() << "\n";

    return 0;
}
