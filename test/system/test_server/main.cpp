#include <docopt/docopt.h>
#include <functional>
#include <iostream>
#include <spdlog/spdlog.h>

#include "project_version.h"

static constexpr auto USAGE =
	R"(Acutis System Test Server.

Usage:
  system_test_server start [--address=<address>] [--port=<port>]
  system_test_server (-h | --help)
  system_test_server --version

Options:
  -h --help            Show this screen.
  --version            Show version.
  --address=<address>  IP Address to bind HTTP server. [default: 0.0.0.0].
  --port=<port>        TCP Port to use for HTTP server. [default: 80].
)";

int main(int argc, const char **argv)
{
	using namespace acutis;

	std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
		{ std::next(argv), std::next(argv, argc) },
		true,// show help if requested
		fmt::format("Acutis System Test Server {}.{}.{}-{}", version::major, version::minor, version::patch,
			version::git_commit_hash));

	int port = args["--port"].asLong();
	std::string address = args["--address"].asString();
	spdlog::info("Server running on {}:{}", address, port);
}
