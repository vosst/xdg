#ifndef XDG_H_
#define XDG_H_

#include <boost/filesystem.hpp>

#include <string>
#include <vector>

namespace xdg
{
struct NotCopyable
{
    NotCopyable() = default;
    NotCopyable(const NotCopyable&) = delete;
    virtual ~NotCopyable() = default;
    NotCopyable& operator=(const NotCopyable&) = delete;
};

struct NotMoveable
{
    NotMoveable() = default;
    NotMoveable(NotMoveable&&) = delete;
    virtual ~NotMoveable() = default;
    NotMoveable& operator=(NotMoveable&&) = delete;
};

class Data : NotCopyable, NotMoveable
{
public:
    // home returns the base directory relative to which user specific
    // data files should be stored.
    virtual boost::filesystem::path home() const;
    // dirs returns the preference-ordered set of base directories to
    // search for data files in addition to the $XDG_DATA_HOME base
    // directory.
    virtual std::vector<boost::filesystem::path> dirs() const;
};

class Config : NotCopyable, NotMoveable
{
public:
    // home returns the base directory relative to which user specific
    // configuration files should be stored.
    virtual boost::filesystem::path home() const;
    // dirs returns the preference-ordered set of base directories to
    // search for configuration files in addition to the
    // $XDG_CONFIG_HOME base directory.
    virtual std::vector<boost::filesystem::path> dirs() const;
};

class Cache : NotCopyable, NotMoveable
{
public:
    // home returns the base directory relative to which user specific
    // non-essential data files should be stored.
    virtual boost::filesystem::path home() const;
};

class Runtime : NotCopyable, NotMoveable
{
public:
    // home returns the base directory relative to which user-specific
    // non-essential runtime files and other file objects (such as
    // sockets, named pipes, ...) should be stored.
    virtual boost::filesystem::path dir() const;
};

// A BaseDirSpecification implements the XDG base dir specification:
//   http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html
class BaseDirSpecification : NotCopyable, NotMoveable
{
public:
    // data returns an immutable Data instance.
    virtual const Data& data() const = 0;
    // config returns an immutable Config instance.
    virtual const Config& config() const = 0;
    // cache returns an immutable Cache instance.
    virtual const Cache& cache() const = 0;
    // runtime returns an immutable Runtime instance.
    virtual const Runtime& runtime() const = 0;
protected:
    BaseDirSpecification() = default;
};

namespace data
{
// home returns the base directory relative to which user specific
// data files should be stored.
boost::filesystem::path home();
// dirs returns the preference-ordered set of base directories to
// search for data files in addition to the $XDG_DATA_HOME base
// directory.
std::vector<boost::filesystem::path> dirs();
}
namespace config
{
// home returns the base directory relative to which user specific
// configuration files should be stored.
boost::filesystem::path home();
// dirs returns the preference-ordered set of base directories to
// search for configuration files in addition to the
// $XDG_CONFIG_HOME base directory.
std::vector<boost::filesystem::path> dirs();
}
namespace cache
{
// home returns the base directory relative to which user specific
// non-essential data files should be stored.
boost::filesystem::path home();
}
namespace runtime
{
// home returns the base directory relative to which user-specific
// non-essential runtime files and other file objects (such as
// sockets, named pipes, ...) should be stored.
boost::filesystem::path dir();
}
}

#endif // XDG_H_
