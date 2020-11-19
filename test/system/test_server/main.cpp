#include <docopt/docopt.h>
#include <functional>
#include <iostream>
#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vector>
#include <filesystem>
#include <thread>
#include <string>

#include "project_version.h"

#include "net/socket_server.h"
#include "net/address.h"

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
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::info);

		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("acutis.log", true);
		file_sink->set_level(spdlog::level::trace);

		spdlog::sinks_init_list sink_list = { console_sink, file_sink };

		auto logger = std::make_shared<spdlog::logger>("acutis", begin(sink_list), end(sink_list));
		logger->set_level(spdlog::level::trace);
		spdlog::set_default_logger(logger);
	}
	catch (const spdlog::spdlog_ex& ex) {
		std::cerr << "Log configuration failed: " << ex.what() << "\n";
	}
}

std::map<std::string, docopt::value> parse_args(int argc, const char** argv) {
	using namespace acutis;

	const std::string server_version = fmt::format(
		"Acutis System Test Server v{}.{}.{}", version::major, version::minor, version::patch);

	return docopt::docopt(USAGE, { std::next(argv), std::next(argv, argc) }, true, server_version);
}

int main(int argc, const char** argv)
{
	using namespace acutis;

	configure_logging();

	try {
		SPDLOG_INFO("Git Commit Hash: {}", version::git_commit_hash);
		SPDLOG_INFO("Current Path: {}", std::filesystem::current_path().string());

		std::map<std::string, docopt::value> args = parse_args(argc, argv);

		long port = args["--port"].asLong();
		std::string address = args["--address"].asString();
		acutis::net::Address bindAddress = net::address_from_string(address);

        std::thread server_thread{[bindAddress, port]()
        {
            acutis::net::Socket_server server;
            server.initialize();
            
            server.listen(bindAddress, static_cast<uint16_t>(port));
        }};

        std::string cmd;
        using namespace std::string_literals;
        do
        {
            std::cin >> cmd;
        } while (cmd != "quit"s);
		SPDLOG_INFO("Quit received");

        server_thread.join();
	}
	catch (const std::exception& ex) {
		SPDLOG_CRITICAL("Critical failure occurred: {}", ex.what());
		return -1;
	}
}
