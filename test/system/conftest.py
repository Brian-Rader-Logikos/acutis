import pytest
from subprocess import Popen
from http.client import HTTPConnection
import os

def pytest_addoption(parser):
    parser.addoption("--server_path", action="store")
    parser.addoption("--port", action="store", default="8085")

@pytest.fixture(scope="class")
def server(request):
    server_path = request.config.getoption("--server_path")
    assert os.path.isfile(server_path)

    with Popen([request.config.getoption("--server_path"),
            "--address", "0.0.0.0",
            "--port", request.config.getoption("--port")]) as process:
        assert process.poll is None
        yield process
        process.terminate()
        process.wait(10)

@pytest.fixture(scope="function")
@pytest.mark.usefixtures("server")
def connection(request):
    conn = HTTPConnection("127.0.0.1", port=request.config.getoption("--port"))
    yield conn


@pytest.fixture(scope="function")
def manual_connection(connection):
    connection.auto_open = 0 # Do not automatically open connection on request
    yield connection

