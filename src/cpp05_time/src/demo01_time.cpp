#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);
  auto node = rclcpp::Node::make_shared("rate_demo");
  // rclcpp::Rate rate(1000ms); // 创建 Rate 对象方式1
  rclcpp::Rate rate(1.0); // 创建 Rate 对象方式2
  while (rclcpp::ok())
  {
    RCLCPP_INFO(node->get_logger(),"hello rate");
    // 休眠
    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}

/* #include "rclcpp/rclcpp.hpp"

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    auto node = rclcpp::Node::make_shared("time_demo");

    // 创建 Time 对象
    rclcpp::Time t1(10500000000L);
    rclcpp::Time t2(2,1000000000L);
    // 通过节点获取当前时刻。
    // rclcpp::Time roght_now = node->get_clock()->now();
    rclcpp::Time roght_now = node->now();
    RCLCPP_INFO(node->get_logger(),"s = %.2f, ns = %ld",t1.seconds(),t1.nanoseconds());
    RCLCPP_INFO(node->get_logger(),"s = %.2f, ns = %ld",t2.seconds(),t2.nanoseconds());
    RCLCPP_INFO(node->get_logger(),"s = %.2f, ns = %ld",roght_now.seconds(),roght_now.nanoseconds());

    rclcpp::shutdown();

    return 0;
}

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    auto node = rclcpp::Node::make_shared("duration_node");

    // 创建 Duration 对象
    rclcpp::Duration du1(1s);
    rclcpp::Duration du2(2,500000000);

    RCLCPP_INFO(node->get_logger(),"s = %.2f, ns = %ld", du2.seconds(),du2.nanoseconds());

    rclcpp::shutdown();
    return 0;
}

#include "rclcpp/rclcpp.hpp"

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    auto node = rclcpp::Node::make_shared("time_opt_demo");

    rclcpp::Time t1(1,500000000);
    rclcpp::Time t2(10,0);

    rclcpp::Duration du1(3,0);
    rclcpp::Duration du2(5,0);

    // 比较
    RCLCPP_INFO(node->get_logger(),"t1 >= t2 ? %d",t1 >= t2);
    RCLCPP_INFO(node->get_logger(),"t1 < t2 ? %d",t1 < t2);
    // 数学运算
    rclcpp::Time t3 = t2 + du1;
    rclcpp::Time t4 = t1 - du1;
    rclcpp::Duration du3 = t2 - t1;

    RCLCPP_INFO(node->get_logger(), "t3 = %.2f",t3.seconds());  
    RCLCPP_INFO(node->get_logger(), "t4 = %.2f",t4.seconds()); 
    RCLCPP_INFO(node->get_logger(), "du3 = %.2f",du3.seconds()); 

    RCLCPP_INFO(node->get_logger(),"--------------------------------------");
    // 比较
    RCLCPP_INFO(node->get_logger(),"du1 >= du2 ? %d", du1 >= du2);
    RCLCPP_INFO(node->get_logger(),"du1 < du2 ? %d", du1 < du2);
    // 数学运算
    rclcpp::Duration du4 = du1 * 3.0;
    rclcpp::Duration du5 = du1 + du2;
    rclcpp::Duration du6 = du1 - du2;

    RCLCPP_INFO(node->get_logger(), "du4 = %.2f",du4.seconds()); 
    RCLCPP_INFO(node->get_logger(), "du5 = %.2f",du5.seconds()); 
    RCLCPP_INFO(node->get_logger(), "du6 = %.2f",du6.seconds()); 

    rclcpp::shutdown();
    return 0;
}

 */