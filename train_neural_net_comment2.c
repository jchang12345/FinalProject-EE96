#include "fann.h"

int main()
{
    const unsigned int num_input = 6;
    // number of input variables, in our case, it should be 6. // const unsigned int num_input = 3;
    const unsigned int num_output = 3;
    // numbe of output variables, in our case, it should be 3. // const unsigned int num_output = 5;
    // shoulder press == 1, bicep curl == -1, none of them == 0
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 36;
    // number of layers, depended on FANNS
    const float desired_error = (const float) 0.0001;
    const unsigned int max_epochs = 5000;
    const unsigned int epochs_between_reports = 100;
//the goal is to train the data but we need to know or roughly know what kind of //motion constitutes what so we can train the data to recognize what is a curl
//and what is a press how to actually define what is what is on the test file.
    struct fann *ann = fann_create_standard(num_layers, num_input,
        num_neurons_hidden, num_output); // Create a fann object (layer3, input6, hidden9, output3)
    
    // operation with FANN

    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

    fann_train_on_file(ann, "test_data.txt", max_epochs,
        epochs_between_reports, desired_error);

    fann_save(ann, "MOTION_TEST.net");

    fann_destroy(ann);

    return 0;
}
