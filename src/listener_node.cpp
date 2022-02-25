#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

void operationCallback(const std_msgs::String::ConstPtr& msg);

int main(int argc, char **argv){
    // node inisialization
    ros::init(argc, argv, "listener_node");

    // for covering all communication function in ROS
    ros::NodeHandle nh;

    // subscriber inisialization
    ros::Subscriber operation_sub =  nh.subscribe("operation_question", 1000, operationCallback);  // subscribe to operation question topic

    ros::spin();
    return 0;
}

void operationCallback(const std_msgs::String::ConstPtr& msg){
    int opand_1, opand_2, result;
    char opr;

    // assign message to a stringstream named operation
    std::stringstream operation(msg->data.c_str());

    // split the stringstream and store it into several variable
    operation >> opand_1 >> opr >> opand_2;

    // find the result value
    switch(opr){
        case '+':
            result = opand_1 + opand_2;
            break;
        case '-':
            result = opand_1 - opand_2;
            break;
        case '*':
            result = opand_1 * opand_2;
            break;
        case '/':
            result = opand_1 / opand_2;
            break;
        case '%':
            result = opand_1 % opand_2;
            break;
    }

    // display the result
    ROS_INFO("the result of %s is %d", msg->data.c_str(), result);
}