INCLUDE(FindPackageHandleStandardArgs)
INCLUDE(HandleLibraryTypes)

SET(Openni_IncludeSearchPaths
  /usr/include/ni/
)

SET(Openni_LibrarySearchPaths
  /usr/lib/
)

FIND_PATH(OPENNI_INCLUDE_DIR XnCppWrapper.h
  PATHS ${Openni_IncludeSearchPaths}
)
FIND_LIBRARY(OPENNI_LIBRARY_OPTIMIZED
  NAMES OpenNI
  PATHS ${Openni_LibrarySearchPaths}
)

# Handle the REQUIRED argument and set the <UPPERCASED_NAME>_FOUND variable
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Openni "Could NOT find Openni. Only required for testing purposes. Please continue."
  OPENNI_LIBRARY_OPTIMIZED
  OPENNI_INCLUDE_DIR
)

IF(OPENNI_FOUND)
 FIND_PACKAGE_MESSAGE(OPENNI_FOUND "Found OpenNI SDK  ${OPENNI_LIBRARY_OPTIMIZED}" "[${OPENNI_LIBRARY_OPTIMIZED}][${OPENNI_INCLUDE_DIR}]")
ENDIF(OPENNI_FOUND)

# Collect optimized and debug libraries
HANDLE_LIBRARY_TYPES(OPENNI)

MARK_AS_ADVANCED(
  OPENNI_INCLUDE_DIR
  OPENNI_LIBRARY_OPTIMIZED
)
