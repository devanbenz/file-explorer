#include <filesystem>
#include <iostream>
#include <ctime>

#include "../include/file-operations.h"

void ListFiles::operation(std::filesystem::path &cwd) const {
    std::cout << "\n\t" << "Directory: " << cwd_ << std::endl;

    std::cout << "\nModified\t\tName\n" << "--------\t\t---------" << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(cwd)) {
        const std::filesystem::path& outfile = std::filesystem::relative(entry);
        std::string outfilename = outfile.string();
        const char* path = outfilename.c_str();
        const std::string last_modified = ListFiles::get_modified_date(const_cast<std::filesystem::path &>(outfile));

        std::cout << last_modified << "\t" << path << std::endl;
    }

}

std::string ListFiles::get_modified_date(std::filesystem::path &file) {
    struct tm buf{};
    auto write_time = std::filesystem::last_write_time(file);
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            write_time - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
            );
    std::time_t tt = std::chrono::system_clock::to_time_t(sctp);

    std::stringstream time_string;
    time_string << std::put_time((localtime( &tt)), "%Y-%m-%d %H:%M:%S");

    return time_string.str();
}
