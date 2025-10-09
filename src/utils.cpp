#include "../inc/main.hpp"
#include "../inc/Points.hpp"

vtkNew<vtkPoints> pointsToVTKPoints(const std::vector<Points>& points) {
    vtkNew<vtkPoints> vtkPoints;
    for (const auto& pt : points) {
        vtkPoints->InsertNextPoint(pt.getX(), pt.getY(), pt.getZ());
    }
    return vtkPoints;
}

vtkNew<vtkCellArray> getCellArray(const std::vector<Points>& points){
    vtkNew<vtkPolyLine> polyLine;

    polyLine->GetPointIds()->SetNumberOfIds(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        polyLine->GetPointIds()->SetId(i, i);
    }
    
    vtkNew<vtkCellArray> cells;
    cells->InsertNextCell(polyLine);
    return cells;
}

vtkNew<vtkPolyDataMapper> pointsToMapper(const std::vector<Points>& points) {
    vtkNew<vtkPoints> vtkPoints = pointsToVTKPoints(points);

    vtkNew<vtkCellArray> cells = getCellArray(points);
    
    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(vtkPoints);
    polyData->SetLines(cells);
    
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(polyData);
    
    return mapper;
}

void appendToMapper(const Points& point, vtkPolyDataMapper& mapper) {
    vtkNew<vtkPoints> vtkPoint;
    vtkPoint->InsertNextPoint(point.getX(), point.getY(), point.getZ());
    mapper.GetInput()->SetPoints(vtkPoint);
    mapper.Update();
}