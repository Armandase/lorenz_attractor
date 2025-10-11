#ifndef MAIN_HPP
# define MAIN_HPP

#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyLine.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkUnsignedCharArray.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

class Points;

typedef struct s_deltas {
    std::function<double(double, double, double)> delta_x;
    std::function<double(double, double, double)> delta_y;
    std::function<double(double, double, double)> delta_z;
}               t_deltas;

vtkNew<vtkPoints> pointsToVTKPoints(const std::vector<Points>& points);
vtkNew<vtkCellArray> getCellArray(const std::vector<Points>& points);
vtkNew<vtkPolyDataMapper> pointsToMapper(const std::vector<Points>& points);
void appendToMapper(const Points& point, vtkPolyDataMapper& mapper);

t_deltas findAttractorByName(const std::string& attractorName);

t_deltas getLorenzAttractorFormula();
t_deltas getHalvorsenAttractorFormula();
t_deltas getAizawaAttractorFormula();
t_deltas getSprottBAttractorFormula();
t_deltas getDadrasAttractorFormula();
t_deltas getRosselAttractorFormula();

#endif