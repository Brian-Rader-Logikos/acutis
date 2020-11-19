import pytest
from subprocess import Popen, PIPE
from http.client import HTTPConnection
import os
import logging
import time

def pytest_addoption(parser):
    parser.addoption("--server_path", action="store")
    parser.addoption("--port", action="store", default="8085")

@pytest.fixture(scope="class")
def server(request):
    server_path = request.config.getoption("--server_path")
    assert os.path.isfile(server_path)

    with Popen([server_path,
            "start",
            "--address", "0.0.0.0",
            "--port", request.config.getoption("--port")], stdin=PIPE, stdout=PIPE, text=True) as process:
        logging.getLogger().info("Running server on %s", server_path)
        time.sleep(1)
        yield process
        stdout_data, stderr_data = process.communicate(timeout=10.0)
        assert "Exiting system_test_server" in stdout_data

@pytest.fixture(scope="function")
def connection(request):
    conn = HTTPConnection("127.0.0.1", port=request.config.getoption("--port"))
    yield conn


@pytest.fixture(scope="function")
def manual_connection(connection):
    logging.getLogger().info("Getting Manual Connection")
    connection.auto_open = 0 # Do not automatically open connection on request
    yield connection

