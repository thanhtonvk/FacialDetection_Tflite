#include "yolov5_tflite.h"

int main()
{

    Prediction out_pred;
    const std::string model_path = "../models/best_facial.tflite";
    const std::string names_path = "../models/labels.names";
    const std::string image_path = "../images/input.png";
    const std::string save_path = "../image/output.png";

    std::vector<std::string> labelNames;

    YOLOV5 model;

    // conf
    model.confThreshold = 0.4;
    model.nmsThreshold = 0.45;
    model.nthreads = 4;

    // Load the saved_model
    model.loadModel(model_path);

    // Load names
    model.getLabelsName(names_path, labelNames);

    std::cout << "\nLabel Count: " << labelNames.size() << "\n"
              << std::endl;


    cv::Mat frame;

    // save video config

    int frame_width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    


    frame = cv::imread(image_path);
    // Predict on the input image
    model.run(frame, out_pred);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "\nModel run time 'milliseconds': " << duration.count() << "\n"
                << std::endl;

    // add the bbox to the image and save it
    auto boxes = out_pred.boxes;
    auto scores = out_pred.scores;
    auto labels = out_pred.labels;

    for (int i = 0; i < boxes.size(); i++)
    {
        auto box = boxes[i];
        auto score = scores[i];
        auto label = labels[i];
        cv::rectangle(frame, box, cv::Scalar(255, 0, 0), 2);
        cv::putText(frame, labelNames[label], cv::Point(box.x, box.y), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(255, 255, 255), 1, cv::LINE_AA);
    }
    cv::imwrite(save_path,frame)
}
