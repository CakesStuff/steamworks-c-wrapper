# - Try to find the steamworks library
#
# Once done, this will define:
#
#  STEAMWORKS_INCLUDE_DIR - the Steamworks include directory
#  STEAMWORKS_LIBRARIES - The libraries needed to use Steamworks

if (NOT STEAMWORKS_INCLUDE_DIR OR NOT STEAMWORKS_LIBRARIES)
	set(LIB_SEARCH_PATHS
		~/Library/Frameworks
		/Library/Frameworks
		/usr/lib
		/usr/lib64
		/usr/local/lib
		/usr/local/lib64
		$ENV{STEAMWORKSROOT}/sdk/redistributable_bin/linux64 #I don't like this. TODO: Make it determine 64/32 bit automatically.
		$ENV{STEAMWORKS_ROOT}/sdk/redistributable_bin/linux64
		$ENV{STEAMWORKS_DIR}/sdk/redistributable_bin/linux64
	)
	FIND_PATH(STEAMWORKS_INCLUDE_DIR steam/steam_api.h
		/usr/include
		/usr/local/include
		$ENV{STEAMWORKSROOT}/sdk/public/
		$ENV{STEAMWORKS_ROOT}/sdk/public/
		$ENV{STEAMWORKS_DIR}/sdk/public/
		DOC "Include path for Steamworks"
	)

	FIND_LIBRARY(STEAMWORKS_LIBRARY NAMES steam_api
		PATHS ${LIB_SEARCH_PATHS}
		DOC "Steamworks library name"
	)
	if (STEAMWORKS_LIBRARY)
		set(STEAMWORKS_LIBRARIES ${STEAMWORKS_LIBRARY})
	else ()
		message("Uh...STEAMWORKS_LIBRARY not set.")
	endif ()
	MARK_AS_ADVANCED(STEAMWORKS_INCLUDE_DIR STEAMWORKS_LIBRARIES)
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(STEAMWORKS DEFAULT_MSG STEAMWORKS_INCLUDE_DIR STEAMWORKS_LIBRARIES)