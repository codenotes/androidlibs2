// Generated by gencpp from file control_msgs/SingleJointPositionFeedback.msg
// DO NOT EDIT!


#ifndef CONTROL_MSGS_MESSAGE_SINGLEJOINTPOSITIONFEEDBACK_H
#define CONTROL_MSGS_MESSAGE_SINGLEJOINTPOSITIONFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace control_msgs
{
template <class ContainerAllocator>
struct SingleJointPositionFeedback_
{
  typedef SingleJointPositionFeedback_<ContainerAllocator> Type;

  SingleJointPositionFeedback_()
    : header()
    , position(0.0)
    , velocity(0.0)
    , error(0.0)  {
    }
  SingleJointPositionFeedback_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , position(0.0)
    , velocity(0.0)
    , error(0.0)  {
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _position_type;
  _position_type position;

   typedef double _velocity_type;
  _velocity_type velocity;

   typedef double _error_type;
  _error_type error;




  typedef boost::shared_ptr< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct SingleJointPositionFeedback_

typedef ::control_msgs::SingleJointPositionFeedback_<std::allocator<void> > SingleJointPositionFeedback;

typedef boost::shared_ptr< ::control_msgs::SingleJointPositionFeedback > SingleJointPositionFeedbackPtr;
typedef boost::shared_ptr< ::control_msgs::SingleJointPositionFeedback const> SingleJointPositionFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace control_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/install_isolated/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/install_isolated/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/install_isolated/share/actionlib_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/install_isolated/share/trajectory_msgs/cmake/../msg'], 'control_msgs': ['/opt/ros/devel_isolated/control_msgs/share/control_msgs/msg', '/opt/ros/src/control_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8cee65610a3d08e0a1bded82f146f1fd";
  }

  static const char* value(const ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8cee65610a3d08e0ULL;
  static const uint64_t static_value2 = 0xa1bded82f146f1fdULL;
};

template<class ContainerAllocator>
struct DataType< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "control_msgs/SingleJointPositionFeedback";
  }

  static const char* value(const ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
Header header\n\
float64 position\n\
float64 velocity\n\
float64 error\n\
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

  static const char* value(const ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.position);
      stream.next(m.velocity);
      stream.next(m.error);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct SingleJointPositionFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::control_msgs::SingleJointPositionFeedback_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "position: ";
    Printer<double>::stream(s, indent + "  ", v.position);
    s << indent << "velocity: ";
    Printer<double>::stream(s, indent + "  ", v.velocity);
    s << indent << "error: ";
    Printer<double>::stream(s, indent + "  ", v.error);
  }
};

} // namespace message_operations
} // namespace ros

#endif // CONTROL_MSGS_MESSAGE_SINGLEJOINTPOSITIONFEEDBACK_H
