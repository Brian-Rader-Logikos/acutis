#include <docopt/docopt.h>
#include <functional>
#include <iostream>
#include <spdlog/spdlog.h>

#include "project_version.h"

static constexpr auto USAGE =
	R"(Acutis Server Demo.

Usage:
  acutis_demo start [--address=<address>] [--port=<port>]
  acutis_demo (-h | --help)
  acutis_demo --version

Options:
  -h --help            Show this screen.
  --version            Show version.
  --address=<address>  IP Address to bind HTTP server. [default: 0.0.0.0].
  --port=<port>        TCP Port to use for HTTP server. [default: 80].
)";

std::map<std::string, docopt::value> parse_args(int argc, const char** argv)
{
	using namespace acutis;

	const std::string server_version =
		fmt::format("Acutis Demo {}.{}.{}", version::major, version::minor, version::patch);

	return docopt::docopt(USAGE, { std::next(argv), std::next(argv, argc) }, true, server_version);
}

int main(int argc, const char** argv)
{
	using namespace acutis;

	try {
		std::map<std::string, docopt::value> args = parse_args(argc, argv);

		int port = args["--port"].asLong();
		std::string address = args["--address"].asString();
		spdlog::info("Server running on {}:{}", address, port);
	}
	catch (const std::exception& ex) {
		SPDLOG_CRITICAL("Critical failure occurred: {}", ex.what());
	}
}
