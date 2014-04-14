######################################################################
# Automatically generated by qmake (2.01a) Mon Apr 14 14:07:29 2014
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              Application \
              FieldsDefinition \
              GlobalFunctions \
              InitialCondition \
              Simulation \
              Application/QCustomPlot \
              Solvers/OneDimensional \
              Solvers/TwoDimensional \
              Solvers/OneDimensional/FluxSolvers \
              Solvers/TwoDimensional/FluxSolvers
INCLUDEPATH += . \
               Application \
               FieldsDefinition \
               GlobalFunctions \
               Simulation \
               Solvers/TwoDimensional \
               Solvers/TwoDimensional/FluxSolvers \
               InitialCondition \
               Solvers/OneDimensional \
               Solvers/OneDimensional/FluxSolvers \
               Application/QCustomPlot

# Input
HEADERS += constants.h \
           Application/PlottingMainWindow.h \
           Application/SimulationMainWindow.h \
           Application/SimulationMainWindow1D.h \
           Application/SimulationMainWindow2D.h \
           Application/ui_mainwindow.h \
           FieldsDefinition/Field1DClass.h \
           FieldsDefinition/Field2DClass.h \
           GlobalFunctions/intInput.h \
           GlobalFunctions/saveDataIntoFile.h \
           GlobalFunctions/saveImageIntoFile.h \
           GlobalFunctions/solveTridiagonalMatrix.h \
           InitialCondition/InitialConditionClass.h \
           InitialCondition/InitialConditionClass_RndNoise.h \
           InitialCondition/InitialConditionClass_Sin.h \
           InitialCondition/InitialConditionClass_Step.h \
           Simulation/Simulation1DClass.h \
           Simulation/Simulation2DClass.h \
           Application/QCustomPlot/qcustomplot.h \
           Solvers/OneDimensional/ForwardEulerScheme.h \
           Solvers/OneDimensional/KurganovTadmor2000Scheme.h \
           Solvers/OneDimensional/KurganovTadmor2ndOrder2000Scheme.h \
           Solvers/OneDimensional/LaxFriedrichsScheme.h \
           Solvers/OneDimensional/MacCormackScheme.h \
           Solvers/OneDimensional/MainSolverClass.h \
           Solvers/OneDimensional/RK4KurganovTadmor2000Scheme.h \
           Solvers/OneDimensional/RK4Scheme.h \
           Solvers/TwoDimensional/ForwardEulerScheme2D.h \
           Solvers/TwoDimensional/LaxFriedrichsScheme2D.h \
           Solvers/TwoDimensional/MainSolverClass2D.h \
           Solvers/TwoDimensional/RK4Scheme2D.h \
           Solvers/OneDimensional/FluxSolvers/FluxCalculatorClass.h \
           Solvers/OneDimensional/FluxSolvers/FluxCalculatorClassLinearReconstructionScheme.h \
           Solvers/OneDimensional/FluxSolvers/FluxCalculatorClassMUSCLScheme.h \
           Solvers/OneDimensional/FluxSolvers/FluxCalculatorPiecewiseParabolicReconstructionScheme.h \
           Solvers/TwoDimensional/FluxSolvers/FluxCalculatorClass2D.h \
           Solvers/TwoDimensional/FluxSolvers/FluxCalculatorClassLinearReconstructionScheme2D.h
SOURCES += main.cpp \
           Application/PlottingMainWindow.cpp \
           Application/SimulationMainWindow.cpp \
           Application/SimulationMainWindow1D.cpp \
           Application/SimulationMainWindow2D.cpp \
           FieldsDefinition/Field1DClass.cpp \
           FieldsDefinition/Field2DClass.cpp \
           GlobalFunctions/intInput.cpp \
           GlobalFunctions/saveDataIntoFile.cpp \
           GlobalFunctions/saveImageIntoFile.cpp \
           GlobalFunctions/solveTridiagonalMatrix.cpp \
           InitialCondition/InitialConditionClass_RndNoise.cpp \
           InitialCondition/InitialConditionClass_Sin.cpp \
           InitialCondition/InitialConditionClass_Step.cpp \
           Simulation/Simulation1DClass.cpp \
           Simulation/Simulation2DClass.cpp \
           Application/QCustomPlot/qcustomplot.cpp \
           Solvers/OneDimensional/ForwardEulerScheme.cpp \
           Solvers/OneDimensional/KurganovTadmor2000Scheme.cpp \
           Solvers/OneDimensional/KurganovTadmor2ndOrder2000Scheme.cpp \
           Solvers/OneDimensional/LaxFriedrichsScheme.cpp \
           Solvers/OneDimensional/MacCormackScheme.cpp \
           Solvers/OneDimensional/RK4KurganovTadmor2000Scheme.cpp \
           Solvers/OneDimensional/RK4Scheme.cpp \
           Solvers/TwoDimensional/ForwardEulerScheme2D.cpp \
           Solvers/TwoDimensional/LaxFriedrichsScheme2D.cpp \
           Solvers/TwoDimensional/RK4Scheme2D.cpp \
           Solvers/OneDimensional/FluxSolvers/FluxCalculatorClassLinearReconstructionScheme.cpp \
           Solvers/OneDimensional/FluxSolvers/FluxCalculatorClassMUSCLScheme.cpp \
           Solvers/OneDimensional/FluxSolvers/FluxCalculatorPiecewiseParabolicReconstructionScheme.cpp \
           Solvers/TwoDimensional/FluxSolvers/FluxCalculatorClassLinearReconstructionScheme2D.cpp
