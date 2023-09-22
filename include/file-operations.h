#pragma once
#include <vector>
#include <filesystem>

template<typename T, typename R>
class FileOperationStrategy {
public:
    FileOperationStrategy();
    virtual ~FileOperationStrategy() = default;
    virtual R operation(T& type) const = 0;
    static void get_cwd();
    static std::filesystem::path cwd_;
};

template<typename T, typename R>
std::filesystem::path FileOperationStrategy<T, R>::cwd_;

template<typename T, typename R>
FileOperationStrategy<T, R>::FileOperationStrategy() {
    get_cwd();
}

template<typename T, typename R>
void FileOperationStrategy<T, R>::get_cwd() {
    cwd_ = std::filesystem::current_path();
}

template<typename T, typename R>
class FileOperations {
private:
    std::unique_ptr<FileOperationStrategy<T, R>> strategy_;
public:
    explicit FileOperations(std::unique_ptr<FileOperationStrategy<T, R>> &&strategy = {}) : strategy_(std::move(strategy)) {};
    void setFileOperationStrategy(std::unique_ptr<FileOperationStrategy<R, T>> &&strategy);
    void run() const;
};

template<typename T, typename R>
void FileOperations<T, R>::run() const {
    if(strategy_) {
        strategy_->operation(strategy_->cwd_);
    }
}

template<typename T, typename R>
void FileOperations<T, R>::setFileOperationStrategy(std::unique_ptr<FileOperationStrategy<R, T>> &&strategy) {
    strategy_ = std::move(strategy);
}

class ListFiles : public FileOperationStrategy<std::filesystem::path, void> {
public:
    void operation(std::filesystem::path &type) const override;
    static std::string get_modified_date(std::filesystem::path &file) ;
};
