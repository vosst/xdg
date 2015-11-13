# xdg

A straightforward implementation of the XDG Base Directory Specification in C++11.
I became tired of retyping and retesting the same functionality over and over again,
so I decided to place my own little helper here.

## Dependencies

 - boost::filesystem: For handling all things filesystem paths.
 - boost::system:: Required by boost::filesystem.
 - boost::test: For testing purposes obviously.

Install with `sudo apt-get install libboost-filesystem-dev libboost-system-dev libboost-test-dev`.

## Example For Small Deployments
```c++
#include <xdg.h>

#include <iostream>

int main()
{
	std::cout << xdg::data().home() << std::endl;
	std::cout << xdg::config().home() << std::endl;
	std::cout << xdg::cache().home() << std::endl;
	std::cout << xdg::runtime().dir() << std::endl;

	return 0;
}
```
