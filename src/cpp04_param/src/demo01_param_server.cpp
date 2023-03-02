/*
    需求：编写参数服务端，设置并操作参数。
    步骤：
        1.包含头文件；
        2.初始化 ROS2 客户端；
        3.定义节点类；
            3-1.声明参数；
            3-2.查询参数；
            3-3.修改参数；
            3-4.删除参数。
        4.创建节点对象指针，调用参数操作函数，并传递给spin函数；
        5.释放资源。

*/

// 1.包含头文件；
#include "rclcpp/rclcpp.hpp"

// 3.定义节点类；
class MinimalParamServer: public rclcpp::Node{
    public:
        MinimalParamServer():Node("minimal_param_server",rclcpp::NodeOptions()
                .allow_undeclared_parameters(true)){       
         //rclcpp::NodeOptions().allow_undeclared_parameters(true)   允许删除参数         
        }
        // 3-1.声明参数；
        void declare_param(){
            // 声明参数并设置默认值
            this->declare_parameter("car_brand","Audi"); 
            this->declare_parameter("height",1.50); 
            this->declare_parameter("wheels",4);   
            // 需要设置 rclcpp::NodeOptions().allow_undeclared_parameters(true),否则非法 
            this->set_parameter(rclcpp::Parameter("undcl_test",100));
        }
        // 3-2.查询参数
        void get_param(){
            RCLCPP_INFO(this->get_logger(),"------------------查----------------");
            // 获取指定parameter
            rclcpp::Parameter car_brand = this->get_parameter("car_brand");
            RCLCPP_INFO(this->get_logger(),"car_brand:%s",car_brand.as_string().c_str());
            RCLCPP_INFO(this->get_logger(),"height:%.2f",this->get_parameter("height").as_double());
            RCLCPP_INFO(this->get_logger(),"wheels:%ld",this->get_parameter("wheels").as_int());
            RCLCPP_INFO(this->get_logger(),"undcl_test:%ld",this->get_parameter("undcl_test").as_int());
            // 判断包含
            RCLCPP_INFO(this->get_logger(),"car_brand? %d",this->has_parameter("car_brand"));
            RCLCPP_INFO(this->get_logger(),"包含car_brandxxxx? %d",this->has_parameter("car_brandxxxx"));
            // 获取所有
            auto params = this->get_parameters({"car_brand","height","wheels"});
            for (auto &param : params)
            {
                RCLCPP_INFO(this->get_logger(),"name = %s, value = %s", param.get_name().c_str(), param.value_to_string().c_str());

            }
        }
        // 3-3.修改参数
        void update_param(){
            RCLCPP_INFO(this->get_logger(),"------------------改----------------");
            this->set_parameter(rclcpp::Parameter("height",1.75));
            RCLCPP_INFO(this->get_logger(),"height:%.2f",this->get_parameter("height").as_double());
        }
        // 3-4.删除参数
        void del_param(){
            RCLCPP_INFO(this->get_logger(),"------------------删----------------");
            // this->undeclare_parameter("car_type");    //不能删除声明declare的参数，set的参数可以删除
            // RCLCPP_INFO(this->get_logger(),"删除操作后，car_type还存在马? %d",this->has_parameter("car_type"));
            RCLCPP_INFO(this->get_logger(),"删除操作前，undcl_test存在马? %d",this->has_parameter("undcl_test"));
            this->undeclare_parameter("undcl_test");
            RCLCPP_INFO(this->get_logger(),"删除操作前，undcl_test存在马? %d",this->has_parameter("undcl_test"));
        }
};

int main(int argc, char ** argv)
{
    // 2.初始化 ROS2 客户端；
    rclcpp::init(argc,argv);

    // 4.创建节点对象指针，调用参数操作函数，并传递给spin函数；
    auto paramServer= std::make_shared<MinimalParamServer>();
    paramServer->declare_param();
    paramServer->get_param();
    paramServer->update_param();
    paramServer->del_param();
    rclcpp::spin(paramServer);

    // 5.释放资源。
    rclcpp::shutdown();
    return 0;
}

