import pytest
from subprocess import Popen
from http.client import HTTPConnection
import os
import logging

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
            "--port", request.config.getoption("--port")]) as process:
        logging.getLogger().error("Running server on %s", server_path)
        yield process
        logging.getLogger().error("Terminating server on %s", server_path)
        process.terminate()
        process.wait(10)

@pytest.fixture(scope="function")
def connection(request):
    conn = HTTPConnection("127.0.0.1", port=request.config.getoption("--port"))
    yield conn


@pytest.fixture(scope="function")
def manual_connection(connection):
    logging.getLogger().error("Getting Manual Connection")
    connection.auto_open = 0 # Do not automatically open connection on request
    yield connection

