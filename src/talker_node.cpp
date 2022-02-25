#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

int main(int argc, char **argv){
    // node inisializatiion
    ros::init(argc, argv, "talker_node");

    // for covering all communication function in ROS
    ros::NodeHandle nh;

    // publisher inisialization
    ros::Publisher operation_pub = nh.advertise<std_msgs::String>("operation_question", 1000);  // publish to operation_question topic

    // since the output is math operation, low frequency(1 Hz) make it readable 
    ros::Rate loop_rate(1);

    srand(time(0));  // set seed for rand() function
    while(ros::ok()){
        std_msgs::String msg;
        std::stringstream operation;

        // making a random math operation
        int opand_1 = (rand() % 10000) + 1;
        int opand_2 = (rand() % 10000) + 1;
        char opr[5] = {'+', '-', '*', '/', '%'};
        operation << opand_1 << " " << opr[rand()%5] << " " << opand_2;

        // assign math operation to the message and publish it
        msg.data = operation.str();
        operation_pub.publish(msg);

        // display the math operation
        ROS_INFO("%s", msg.data.c_str());

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
