PROJECT(TESTUTIL)

SET(TESTUTIL_LIB_SRC
	Base64.cpp
	RegressionTest.cpp
	Measurement.cpp
	MeasurementVisitor.cpp
	diff.cpp
)

INCLUDE_DIRECTORIES("${EXPAT_BINARY_DIR}" "${TESTUTIL_BINARY_DIR}" "${FILEUTIL_BINARY_DIR}")


CONFIGURE_FILE("${TESTUTIL_SOURCE_DIR}/.NoDartCoverage"
  "${TESTUTIL_BINARY_DIR}/.NoDartCoverage")
CONFIGURE_FILE("${TESTUTIL_SOURCE_DIR}/testutilConfigure.h.in"
  "${TESTUTIL_BINARY_DIR}/testutilConfigure.h" IMEDIATE) 
 

ADD_LIBRARY(testutil ${TESTUTIL_LIB_SRC})
TARGET_LINK_LIBRARIES(testutil expat fileutil)