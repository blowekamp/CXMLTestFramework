
#create the teting file and list of tests
CREATE_TEST_SOURCELIST ( TestingFrameworkTests1_SRC
  tkTests1.cxx
  tfHeaderTest.cxx  
  tfRegressionTestOutputTest1.cxx
)

#create the teting file and list of tests
CREATE_TEST_SOURCELIST ( TestingFrameworkTests2_SRC
  tkTests2.cxx  
  tfRegressionTestTest1.cxx
  tfRegressionTestTest2.cxx
  tfRegressionTestTest3.cxx
)

INCLUDE_DIRECTORIES( ${TESTINGFRAMEWORK_SOURCE_DIR} )

ADD_EXECUTABLE( tkTests1 ${TestingFrameworkTests1_SRC} )
TARGET_LINK_LIBRARIES (tkTests1 testingframework fileutil )

ADD_EXECUTABLE( tkTests2 ${TestingFrameworkTests2_SRC} )
TARGET_LINK_LIBRARIES (tkTests2 testingframework fileutil )


SET ( TESTINGFRAMEWORK_TEST1 ${EXECUTABLE_OUTPUT_PATH}/tkTests1 )

SET ( TestsToRun ${TestingFrameworkTests1_SRC} )
REMOVE ( TestsToRun TestingFrameworkTests1.cxx ) 
FOREACH ( test ${TestsToRun} )
  GET_FILENAME_COMPONENT ( TName ${test} NAME_WE )
  ADD_TEST ( ${TName} ${TESTINGFRAMEWORK_TEST1} ${TName} )
ENDFOREACH ( test )


SET ( TESTINGFRAMEWORK_TEST2 ${EXECUTABLE_OUTPUT_PATH}/tkTests2 )
SET ( TESTINGFRAMEWORK_XML_DATA ${CMAKE_CURRENT_SOURCE_DIR}/xml )

SET ( TestsToRun ${TestingFrameworkTests2_SRC} )
REMOVE ( TestsToRun TestingFrameworkTests2.cxx ) 
FOREACH ( test ${TestsToRun} )
  GET_FILENAME_COMPONENT ( TName ${test} NAME_WE )
  ADD_TEST ( ${TName} ${TESTINGFRAMEWORK_TEST2} ${TName} -I ${TESTINGFRAMEWORK_XML_DATA}/${TName}.xml )
ENDFOREACH ( test )

