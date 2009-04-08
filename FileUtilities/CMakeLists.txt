PROJECT(Micro)


# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

ADD_SUBDIRECTORY( fileutil )

ADD_EXECUTABLE(seriesToITK ImageSeriesReadWrite.cxx)
TARGET_LINK_LIBRARIES(seriesToITK ITKIO  fileutil)  


ADD_EXECUTABLE(itkToSeries ImageReadImageSeriesWrite.cxx)
TARGET_LINK_LIBRARIES(itkToSeries ITKIO  fileutil)  



ADD_EXECUTABLE(initialProcess InitialProcess.cxx)
TARGET_LINK_LIBRARIES(initialProcess ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(binaryThreshold BinaryThresholdImageFilter.cxx)
TARGET_LINK_LIBRARIES(binaryThreshold ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)

ADD_EXECUTABLE(bilateral BilateralImageFilter.cxx)
TARGET_LINK_LIBRARIES(bilateral  ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)

ADD_EXECUTABLE(canneyEdge CannyEdgeDetectionImageFilter.cxx)
TARGET_LINK_LIBRARIES(canneyEdge ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)

ADD_EXECUTABLE(initialRegister InitialRegistration.cxx)
TARGET_LINK_LIBRARIES(initialRegister ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)

#ADD_EXECUTABLE(deformable4Register DeformableRegistration4.cxx)
#TARGET_LINK_LIBRARIES(deformable4Register ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(deformable5Register DeformableRegistration5.cxx)
TARGET_LINK_LIBRARIES(deformable5Register ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)

ADD_EXECUTABLE(deformable6Register DeformableRegistration6.cxx)
TARGET_LINK_LIBRARIES(deformable6Register ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)

#ADD_EXECUTABLE(anotherRegister AnotherRegistration.cxx)
#TARGET_LINK_LIBRARIES(anotherRegister ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)

ADD_EXECUTABLE(circleDetection HoughTransform3DCirclesImageFilter.cxx)
TARGET_LINK_LIBRARIES(circleDetection ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(gradDiffusion GradientAnisotropicDiffusionImageFilter.cxx)
TARGET_LINK_LIBRARIES(gradDiffusion ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(curvDiffusion CurvatureAnisotropicDiffusionImageFilter.cxx)
TARGET_LINK_LIBRARIES(curvDiffusion ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(updateCircles UpdateCircles.cxx)
TARGET_LINK_LIBRARIES(updateCircles ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(learnCircles LearnCircles.cxx)
TARGET_LINK_LIBRARIES(learnCircles ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)



ADD_EXECUTABLE(resample ResampleImageFilter.cxx)
TARGET_LINK_LIBRARIES(resample ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(dialate DialateImageFilter.cxx)
TARGET_LINK_LIBRARIES(dialate ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(erode ErodeImageFilter.cxx)
TARGET_LINK_LIBRARIES(erode ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)




ADD_EXECUTABLE(laplacianLevelset LaplacianSegmentationLevelSetImageFilter.cxx)
TARGET_LINK_LIBRARIES(laplacianLevelset ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)



ADD_EXECUTABLE(cannyLevelset CannySegmentationLevelSetImageFilter.cxx)
TARGET_LINK_LIBRARIES(cannyLevelset ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)



ADD_EXECUTABLE(thresholdLevelset ThresholdSegmentationLevelSetImageFilter.cxx)
TARGET_LINK_LIBRARIES(thresholdLevelset ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(fastMarchingLevelset FastMarchingSegmentationLevelSetImageFilter.cxx)
TARGET_LINK_LIBRARIES(fastMarchingLevelset ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(connectedComponents ConnectedComponents.cxx)
TARGET_LINK_LIBRARIES(connectedComponents ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)


ADD_EXECUTABLE(connectedThreshold ConnectedThresholdImageFilter.cxx)
TARGET_LINK_LIBRARIES(connectedThreshold ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)




ADD_EXECUTABLE(mergeMasks OrImageFilter.cxx)
TARGET_LINK_LIBRARIES(mergeMasks ITKAlgorithms ITKStatistics ITKNumerics ITKIO fileutil)
