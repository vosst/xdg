#include <xdg.h>

#include <boost/algorithm/string.hpp>

#include <cstdlib>
#include <stdexcept>

namespace fs = boost::filesystem;

namespace
{

fs::path throw_if_not_absolute(const fs::path& p)
{
    if (p.has_root_directory())
        return p;

    throw std::runtime_error{"Directores MUST be absolute."};
}

namespace env
{
std::string get(const std::string& key, const std::string& default_value)
{
    if (auto value = std::getenv(key.c_str()))
        return value;
    return default_value;
}

std::string get_or_throw(const std::string& key)
{
    if (auto value = std::getenv(key.c_str()))
    {
        return value;
    }

    throw std::runtime_error{key + " not set in environment"};
}

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

fs::path xdg::Data::home() const
{
    fs::path p{env::get(env::xdg_data_home, "")};

    if (fs::is_directory(p))
        return p;

    return fs::path{env::get_or_throw("HOME")} / ".local" / "share";
}

std::vector<fs::path> xdg::Data::dirs() const
{
    std::vector<std::string> tokens;
    auto dirs = env::get(env::xdg_data_dirs, "/usr/local/share/:/usr/share/");
    tokens = boost::split(tokens, dirs, boost::is_any_of(":"));
    std::vector<fs::path> result;
    for (const auto& token : tokens)
    {
        fs::path p(token);
        if (fs::is_directory(p))
            result.push_back(p);
    }
    return result;
}

fs::path xdg::Config::home() const
{
    fs::path p{env::get(env::xdg_config_home, "")};

    if (fs::is_directory(p))
        return throw_if_not_absolute(p);

    return throw_if_not_absolute(fs::path{env::get_or_throw("HOME")} / ".config");
}

std::vector<fs::path> xdg::Config::dirs() const
{
    std::vector<std::string> tokens;
    auto dirs = env::get(env::xdg_config_dirs, "/etc/xdg");
    tokens = boost::split(tokens, dirs, boost::is_any_of(":"));
    std::vector<fs::path> result;
    for (const auto& token : tokens)
    {
        fs::path p(token);
        if (fs::is_directory(p))
            result.push_back(throw_if_not_absolute(p));
    }
    return result;
}

fs::path xdg::Cache::home() const
{
    fs::path p{env::get(env::xdg_cache_home, "")};

    if (fs::is_directory(p))
        return throw_if_not_absolute(p);

    return throw_if_not_absolute(fs::path{env::get_or_throw("HOME")} / ".cache");
}

fs::path xdg::Runtime::dir() const
{
    fs::path p{env::get(env::xdg_config_home, "")};

    if (fs::is_directory(p))
        return throw_if_not_absolute(p);

    // We do not fall back gracefully and instead throw, dispatching to calling
    // code for handling the case of a safe user-specfic runtime directory missing.
    throw std::runtime_error{"Runtime directory not set"};
}

boost::filesystem::path xdg::data::home()
{
    return impl::BaseDirSpecification::instance().data().home();
}

std::vector<boost::filesystem::path> xdg::data::dirs()
{
    return impl::BaseDirSpecification::instance().data().dirs();
}

boost::filesystem::path xdg::config::home()
{
    return impl::BaseDirSpecification::instance().config().home();
}

std::vector<boost::filesystem::path> xdg::config::dirs()
{
    return impl::BaseDirSpecification::instance().config().dirs();
}

boost::filesystem::path xdg::cache::home()
{
    return impl::BaseDirSpecification::instance().cache().home();
}

boost::filesystem::path xdg::runtime::dir()
{
    return impl::BaseDirSpecification::instance().runtime().dir();
}
