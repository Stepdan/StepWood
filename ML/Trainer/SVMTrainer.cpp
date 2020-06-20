#include <iostream>
#include <fstream>

#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>

#include "SVMTrainer.h"

using namespace dlib;

namespace ML {

class SVMTrainer::Impl
{
public:
    void Train(const std::string& path)
    {
        dlib::array<array2d<unsigned char> > images_train;
        std::vector<std::vector<rectangle> > boxes_train;
        load_image_dataset(images_train, boxes_train, path + "/Data.xml");
        upsample_image_dataset<pyramid_down<2> >(images_train, boxes_train);
        std::cout << "num training images: " << images_train.size() << std::endl;
        typedef scan_fhog_pyramid<pyramid_down<6> > image_scanner_type;
        image_scanner_type scanner;
        scanner.set_detection_window_size(80, 80);
        structural_object_detection_trainer<image_scanner_type> trainer(scanner);
        trainer.set_num_threads(6);
        // The trainer is a kind of support vector machine and therefore has the usual SVM
        // C parameter.  In general, a bigger C encourages it to fit the training data
        // better but might lead to overfitting.  You must find the best C value
        // empirically by checking how well the trained detector works on a test set of
        // images you haven't trained on.  Don't just leave the value set at 1.  Try a few
        // different C values and see what works best for your data.
        trainer.set_c(1);
        // We can tell the trainer to print it's progress to the console if we want.
        trainer.be_verbose();
        // The trainer will run until the "risk gap" is less than 0.01.  Smaller values
        // make the trainer solve the SVM optimization problem more accurately but will
        // take longer to train.  For most problems a value in the range of 0.1 to 0.01 is
        // plenty accurate.  Also, when in verbose mode the risk gap is printed on each
        // iteration so you can see how close it is to finishing the training.
        trainer.set_epsilon(0.01);
        object_detector<image_scanner_type> detector = trainer.train(images_train, boxes_train);

        // Now that we have a face detector we can test it.  The first statement tests it
        // on the training data.  It will print the precision, recall, and then average precision.
        std::cout << "training results: " << test_object_detection_function(detector, images_train, boxes_train) << std::endl;
        serialize("wood_log_detector.svm") << detector;
    }

private:
};

//.....................................................................................

SVMTrainer::SVMTrainer()
    : m_impl(std::make_unique<Impl>())
{}

//.....................................................................................

SVMTrainer::~SVMTrainer() = default;

//.....................................................................................

void SVMTrainer::Train(const std::string &path)
{
    m_impl->Train(path);
}

}
