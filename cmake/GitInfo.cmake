find_package(Git)
if(Git_FOUND)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	execute_process(
		COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_COMMIT_HASH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	function (git_get_status)
		execute_process(
			COMMAND ${GIT_EXECUTABLE} status --short
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			OUTPUT_VARIABLE git_status
			OUTPUT_STRIP_TRAILING_WHITESPACE
		)

		if(git_status STREQUAL "")
			set(GIT_HAS_LOCAL_CHANGES FALSE PARENT_SCOPE)
		else()
			set(GIT_HAS_LOCAL_CHANGES TRUE PARENT_SCOPE)
		endif()
	endfunction()

	git_get_status()

	message("GIT_BRANCH: ${GIT_BRANCH}")
	message("GIT_COMMIT_HASH: ${GIT_COMMIT_HASH}")
	message("GIT_IS_DIRTY: ${GIT_IS_DIRTY}")

endif()
