/*  
    需求：订阅发布方发布的学生消息，并输出到终端。
*/

// 1.包含头文件；
#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"

// using std::placeholders::_1;
using base_interfaces_demo::msg::Student;
// 3.定义节点类；
class ListenerStu : public rclcpp::Node
{
  public:
    ListenerStu()
    : Node("sub_stu_c_node")
    {
      // 3-1.创建订阅方；
      subscription_ = this->create_subscription<Student>("topic_stu", 10, std::bind(&ListenerStu::topic_callback, this, std::placeholders::_1));
    }

  private:
    // 3-2.处理订阅到的消息；
    void topic_callback(const Student & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "订阅的学生消息：name=%s,age=%d,height=%.2f", msg.name.c_str(),msg.age, msg.height);
    }
    rclcpp::Subscription<Student>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  // 2.初始化 ROS2 客户端；
  rclcpp::init(argc, argv);
  // 4.调用spin函数，并传入节点对象指针。
  rclcpp::spin(std::make_shared<ListenerStu>());
  // 5.释放资源；
  rclcpp::shutdown();
  return 0;
}
