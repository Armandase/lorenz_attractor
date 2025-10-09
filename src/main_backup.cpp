#include "../inc/main.hpp"
#include "../inc/Points.hpp"

std::vector<Points> readDataFile(const std::string& filename) {
    std::vector<Points> points;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return points;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<double> values;
        
        while (std::getline(ss, token, ';')) {
            try {
                values.push_back(std::stod(token));
            } catch (const std::exception& e) {
                std::cerr << "Error parsing value: " << token << std::endl;
                continue;
            }
        }
        
        if (values.size() == 4) {
            Points point(values[0], values[1], values[2], values[3]);
            points.push_back(point);
        }
    }
    
    file.close();
    std::cout << "Loaded " << points.size() << " points from " << filename << std::endl;
    return points;
}



int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        std::cerr << "Example: " << argv[0] << " attractor_log.txt" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::string filename = argv[1];
    
    // Read data from file
    std::vector<Points> lorenzPoints = readDataFile(filename);
    
    if (lorenzPoints.empty()) {
        std::cerr << "No data points loaded. Exiting." << std::endl;
        return EXIT_FAILURE;
    }
    
    // Convert points to VTK mapper
    vtkNew<vtkPolyDataMapper> mapper = pointsToMapper(lorenzPoints);
    
    // Setup actor
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
    actor->GetProperty()->SetLineWidth(2.0);
    
    // Setup renderer
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("Black").GetData());
    
    // Add title text
    vtkNew<vtkTextActor> titleActor;
    titleActor->SetInput("Lorenz Attractor Visualization");
    titleActor->GetTextProperty()->SetFontSize(24);
    titleActor->GetTextProperty()->SetColor(colors->GetColor3d("White").GetData());
    titleActor->SetPosition(10, 10);
    renderer->AddActor2D(titleActor);
    
    // Setup render window
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(1024, 768);
    renderWindow->SetWindowName("Lorenz Attractor");
    
    // Setup interactor
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);
    
    // Add axes widget
    vtkNew<vtkAxesActor> axes;
    axes->SetTotalLength(10.0, 10.0, 10.0);
    axes->SetXAxisLabelText("X");
    axes->SetYAxisLabelText("Y");
    axes->SetZAxisLabelText("Z");
    
    vtkNew<vtkOrientationMarkerWidget> widget;
    widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    widget->SetOrientationMarker(axes);
    widget->SetInteractor(renderWindowInteractor);
    widget->SetViewport(0.0, 0.0, 0.2, 0.2);
    widget->SetEnabled(1);
    widget->InteractiveOn();
    
    // Reset camera to view all data
    renderer->ResetCamera();
    
    // Start interaction
    renderWindow->Render();
    renderWindowInteractor->Start();
    
    return EXIT_SUCCESS;
}
