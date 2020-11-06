#include <docopt/docopt.h>
#include <functional>
#include <iostream>
#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vector>

#include "project_version.h"

#include "net/socket_server.h"

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

void configure_logging()
{
	try {
		auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console->set_level(spdlog::level::info);

		auto file = std::make_shared<spdlog::sinks::basic_file_sink_mt>("acutis.log", true);
		file->set_level(spdlog::level::trace);

		std::vector<spdlog::sink_ptr> sinks{ console, file };

		spdlog::init_thread_pool(8192, 1);
		auto logger = std::make_shared<spdlog::async_logger>("acutis", sinks.begin(), sinks.end(),
			spdlog::thread_pool(), spdlog::async_overflow_policy::block);
		logger->set_level(spdlog::level::debug);
		logger->debug("Logger configured");
		spdlog::register_logger(logger);
	}
	catch (const spdlog::spdlog_ex& ex) {
		std::cerr << "Log configuration failed: " << ex.what() << "\n";
	}
}

int main(int argc, const char** argv)
{
	using namespace acutis;

	configure_logging();

	const std::string server_version = fmt::format(
		"Acutis System Test Server v{}.{}.{}", version::major, version::minor, version::patch);

	spdlog::get("acutis")->debug(server_version);
	spdlog::get("acutis")->debug("Git Commit Hash: {}", version::git_commit_hash);

	std::map<std::string, docopt::value> args =
		docopt::docopt(USAGE, { std::next(argv), std::next(argv, argc) }, true, server_version);

	long port = args["--port"].asLong();
	std::string address = args["--address"].asString();

	spdlog::get("acutis")->info("Binding server on {}:{}", address, port);

	acutis::net::Socket_server server;
	acutis::net::Address bindAddress{ address };
	server.listen(bindAddress, port);
}
