#include "../inc/main.hpp"
#include "../inc/Points.hpp"
#include "../inc/Attractor.hpp"
#include <vtkCallbackCommand.h>

struct CallbackData {
    Attractor* attractor;
    vtkPolyData* polyData;
    vtkRenderer* renderer;
    std::vector<Points>* pointsHistory;
    int nbIter;
    int currentIteration;
};

void TimerCallback(vtkObject* caller, long unsigned int eventId, 
                   void* clientData, void* callData) {
    (void)caller;
    (void)eventId;
    (void)callData;
    
    CallbackData* data = static_cast<CallbackData*>(clientData);
    
    if (data->currentIteration >= data->nbIter) {
        std::cout << "\n Simulation ended, total: " << data->pointsHistory->size() << " points" << std::endl;
        return;
    }
    
    data->attractor->updateAttractor();
    Points newPoint(data->attractor->getX(), 
                   data->attractor->getY(), 
                   data->attractor->getZ());
    data->pointsHistory->push_back(newPoint);
    
    vtkPoints* vtkPts = data->polyData->GetPoints();
    vtkPts->InsertNextPoint(newPoint.getX(), newPoint.getY(), newPoint.getZ());
    
    // update lines to connect all points
    vtkCellArray* lines = data->polyData->GetLines();
    lines->Reset();
    
    vtkNew<vtkPolyLine> polyLine;
    polyLine->GetPointIds()->SetNumberOfIds(data->pointsHistory->size());
    for (size_t i = 0; i < data->pointsHistory->size(); ++i) {
        polyLine->GetPointIds()->SetId(i, i);
    }
    lines->InsertNextCell(polyLine);
    
    // notify VTK data as been updated
    data->polyData->Modified();
    data->polyData->GetPoints()->Modified();
    data->polyData->GetLines()->Modified();
    data->currentIteration++;
    
    // if (data->currentIteration % 500 == 0) {
        // data->renderer->ResetCamera();
    // }
    
    data->renderer->GetRenderWindow()->Render();
}



int main(int argc, char** argv) {
    double x0 = 1.0, y0 = 1.0, z0 = 1.0;
    double dt = 0.01; // Time step
    int nbIter = 10000;
    int timerInterval = 1;

    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " [nb_iterations] [timer_interval_ms] [time_step_ms]" << std::endl;
        std::cout << "Using default values: nb_iterations="<< nbIter << ", timer_interval_ms=" << timerInterval << ", time_step_ms=" << dt << std::endl;
    }
    if (argc >= 2) {
        nbIter = std::atoi(argv[1]);
    }
    if (argc >= 3) {
        timerInterval = std::atoi(argv[2]);
    }
    if (argc >= 4) {
        dt = std::atof(argv[3]);
    }

    std::cout << "Config:" << std::endl;
    std::cout << " - nb_iterations: " << nbIter << std::endl;
    std::cout << " - timer_interval_ms: " << timerInterval << std::endl;
    std::cout << " - time_step: " << dt << std::endl;
    std::cout << " - initial_point: (" << x0 << ", " << y0 << ", " << z0 << ")" << std::endl;
    
    Attractor attractor(x0, y0, z0, dt);
    
    std::vector<Points> pointsHistory;
    Points initialPoint(x0, y0, z0);
    pointsHistory.push_back(initialPoint);
    
    vtkNew<vtkPoints> vtkPoints;
    vtkPoints->InsertNextPoint(x0, y0, z0);
    
    vtkNew<vtkCellArray> lines;
    
    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(vtkPoints);
    polyData->SetLines(lines);
    
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(polyData);
    
    // Setup actor it's used to represent an entity in a rendering scene
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
    titleActor->SetInput("Lorenz Attractor - Real-time Simulation");
    titleActor->GetTextProperty()->SetFontSize(24);
    titleActor->GetTextProperty()->SetColor(colors->GetColor3d("White").GetData());
    titleActor->SetPosition(10, 10);
    renderer->AddActor2D(titleActor);
    
    // Setup render window
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(1024, 768);
    renderWindow->SetWindowName("Lorenz Attractor - Real-time");
    
    // interactor: handles mouse and keyboard events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);
    
    // Add axes
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
    
    // callback data used to iterate & update the attractor
    CallbackData callbackData;
    callbackData.attractor = &attractor;
    callbackData.polyData = polyData;
    callbackData.renderer = renderer;
    callbackData.pointsHistory = &pointsHistory;
    callbackData.nbIter = nbIter;
    callbackData.currentIteration = 0;
    
    vtkNew<vtkCallbackCommand> timerCallback;
    timerCallback->SetCallback(TimerCallback);
    timerCallback->SetClientData(&callbackData);
    
    // Add the callback to the interactor
    renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, timerCallback);
    
    // create a repeating timer (pseudo loop)
    renderWindowInteractor->CreateRepeatingTimer(timerInterval);
    
    // Initialize and start the interactor
    renderWindowInteractor->Initialize();
    vtkCamera* camera = renderer->GetActiveCamera();
    camera->SetPosition(50, 50, 50);
    camera->SetFocalPoint(0, 0, 25);
    camera->SetViewUp(0, 0, 1);
    renderer->ResetCamera();
    
    renderWindow->Render();
    renderWindowInteractor->Start();
    
    std::cout << "\nProgramme terminé." << std::endl;
    
    return EXIT_SUCCESS;
}
