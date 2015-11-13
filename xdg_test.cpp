#include <xdg.h>

#include <boost/test/unit_test.hpp>

#include <cstdlib>
#include <iostream>

BOOST_AUTO_TEST_CASE(XdgDataHomeThrowsForRelativeDirectoryFromEnv)
{
    ::setenv("XDG_DATA_HOME", "tmp", 1);
    BOOST_CHECK_THROW(xdg::data::home(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(XdgDataHomeReturnsDefaultValueForEmptyEnv)
{
    ::setenv("HOME", "/tmp", 1);
    ::setenv("XDG_DATA_HOME", "", 1);
    BOOST_CHECK_EQUAL("/tmp/.local/share", xdg::data::home());
}

BOOST_AUTO_TEST_CASE(XdgConfigHomeThrowsForRelativeDirectoryFromEnv)
{
    ::setenv("XDG_CONFIG_HOME", "tmp", 1);
    BOOST_CHECK_THROW(xdg::config::home(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(XdgConfigHomeReturnsDefaultValueForEmptyEnv)
{
    ::setenv("HOME", "/tmp", 1);
    ::setenv("XDG_CONFIG_HOME", "", 1);
    BOOST_CHECK_EQUAL("/tmp/.config", xdg::config::home());
}

BOOST_AUTO_TEST_CASE(XdgCacheHomeThrowsForRelativeDirectoryFromEnv)
{
    ::setenv("XDG_CACHE_HOME", "tmp", 1);
    BOOST_CHECK_THROW(xdg::cache::home(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(XdgCacheHomeReturnsDefaultValueForEmptyEnv)
{
    ::setenv("HOME", "/tmp", 1);
    ::setenv("XDG_CACHE_HOME", "", 1);
    BOOST_CHECK_EQUAL("/tmp/.cache", xdg::cache::home());
}

BOOST_AUTO_TEST_CASE(XdgRuntimeDirThrowsForRelativeDirectoryFromEnv)
{
    ::setenv("XDG_RUNTIME_DIR", "tmp", 1);
    BOOST_CHECK_THROW(xdg::runtime::dir(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(XdgRuntimeDirThrowsForEmptyEnv)
{
    ::setenv("XDG_RUNTIME_DIR", "", 1);
    BOOST_CHECK_THROW(xdg::runtime::dir(), std::runtime_error);
}

