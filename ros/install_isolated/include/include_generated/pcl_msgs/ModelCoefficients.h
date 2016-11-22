// Generated by gencpp from file pcl_msgs/ModelCoefficients.msg
// DO NOT EDIT!


#ifndef PCL_MSGS_MESSAGE_MODELCOEFFICIENTS_H
#define PCL_MSGS_MESSAGE_MODELCOEFFICIENTS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace pcl_msgs
{
template <class ContainerAllocator>
struct ModelCoefficients_
{
  typedef ModelCoefficients_<ContainerAllocator> Type;

  ModelCoefficients_()
    : header()
    , values()  {
    }
  ModelCoefficients_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , values(_alloc)  {
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _values_type;
  _values_type values;




  typedef boost::shared_ptr< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> const> ConstPtr;

}; // struct ModelCoefficients_

typedef ::pcl_msgs::ModelCoefficients_<std::allocator<void> > ModelCoefficients;

typedef boost::shared_ptr< ::pcl_msgs::ModelCoefficients > ModelCoefficientsPtr;
typedef boost::shared_ptr< ::pcl_msgs::ModelCoefficients const> ModelCoefficientsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::pcl_msgs::ModelCoefficients_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace pcl_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/install_isolated/share/std_msgs/cmake/../msg'], 'pcl_msgs': ['/opt/ros/src/pcl_msgs/msg'], 'sensor_msgs': ['/opt/ros/install_isolated/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/install_isolated/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ca27dea75e72cb894cd36f9e5005e93e";
  }

  static const char* value(const ::pcl_msgs::ModelCoefficients_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xca27dea75e72cb89ULL;
  static const uint64_t static_value2 = 0x4cd36f9e5005e93eULL;
};

template<class ContainerAllocator>
struct DataType< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >
{
  static const char* value()
  {
    return "pcl_msgs/ModelCoefficients";
  }

  static const char* value(const ::pcl_msgs::ModelCoefficients_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
float32[] values\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::pcl_msgs::ModelCoefficients_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.values);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct ModelCoefficients_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::pcl_msgs::ModelCoefficients_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::pcl_msgs::ModelCoefficients_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "values[]" << std::endl;
    for (size_t i = 0; i < v.values.size(); ++i)
    {
      s << indent << "  values[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.values[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // PCL_MSGS_MESSAGE_MODELCOEFFICIENTS_H
