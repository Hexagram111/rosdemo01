/*  
    需求：订阅发布方发布的消息，并输出到终端。
    步骤：
        1.包含头文件；
        2.初始化 ROS2 客户端；
        3.定义节点类；
            3-1.创建订阅方；
            3-2.处理订阅到的消息。
        4.调用spin函数，并传入节点对象指针；
        5.释放资源。
*/

// 1.包含头文件；
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
// using std::placeholders::_1;

// 3.定义节点类；
class Listener : public rclcpp::Node
{
  public:
    Listener()
    : Node("listener_c_node")
    {
      RCLCPP_INFO(this->get_logger(),"订阅节点Listener已创建!");
      // 3-1.创建订阅方；
      /*
          模板：消息类型；
          参数：
              1.话题名称
              2.QoS,队列长度
              3.回调函数
          返回值：订阅对象指针
      */
      subscription_ = this->create_subscription<std_msgs::msg::String>("topic_name", 10, std::bind(&Listener::topic_callback, this, std::placeholders::_1));
    }

  private:
    // 3-2.处理订阅到的消息；
    void topic_callback(const std_msgs::msg::String & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "订阅的消息： '%s'", msg.data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  // 2.初始化 ROS2 客户端；
  rclcpp::init(argc, argv);
  // 4.调用spin函数，并传入节点对象指针。
  rclcpp::spin(std::make_shared<Listener>());
  // 5.释放资源；
  rclcpp::shutdown();
  return 0;
}
