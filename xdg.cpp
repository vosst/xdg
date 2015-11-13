#include <xdg.h>

#include <cstdlib>

#include <stdexcept>

namespace
{
namespace env
{
std::string get_or_throw(const std::string& key)
{
    if (auto value = std::getenv(key.c_str()))
    {
        return value;
    }

    throw std::runtime_error{key + " not set in environment"};
}
}

namespace env
{
constexpr const char* xdg_data_home{"XDG_DATA_HOME"};
constexpr const char* xdg_data_dirs{"XDG_DATA_DIRS"};
constexpr const char* xdg_config_home{"XDG_CONFIG_HOME"};
constexpr const char* xdg_config_dirs{"XDG_CONFIG_DIRS"};
constexpr const char* xdg_cache_home{"XDG_CACHE_HOME"};
constexpr const char* xdg_runtime_dir{"XDG_RUNTIME_DIR"};
}

namespace impl
{
class BaseDirSpecification : public xdg::BaseDirSpecification
{
public:
    static const BaseDirSpecification& instance()
    {
        static const BaseDirSpecification spec;
        return spec;
    }

    BaseDirSpecification()
    {
    }

    const xdg::Data& data() const override
    {
        return data_;
    }

    const xdg::Config& config() const override
    {
        return config_;
    }

    const xdg::Cache& cache() const override
    {
        return cache_;
    }

    const xdg::Runtime& runtime() const override
    {
        return runtime_;
    }

private:
    xdg::Data data_;
    xdg::Config config_;
    xdg::Cache cache_;
    xdg::Runtime runtime_;
};
}
}

std::string xdg::data::home()
{
    return impl::BaseDirSpecification::instance().data().home();
}

std::vector<std::string> xdg::data::dirs()
{
    return impl::BaseDirSpecification::instance().data().dirs();
}

std::string xdg::config::home()
{
    return impl::BaseDirSpecification::instance().config().home();
}

std::vector<std::string> xdg::config::dirs()
{
    return impl::BaseDirSpecification::instance().config().dirs();
}

std::string xdg::cache::home()
{
    return impl::BaseDirSpecification::instance().cache().home();
}

std::string xdg::runtime::dir()
{
    return impl::BaseDirSpecification::instance().runtime().dir();
}
