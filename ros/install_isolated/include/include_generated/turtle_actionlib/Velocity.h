// Generated by gencpp from file turtle_actionlib/Velocity.msg
// DO NOT EDIT!


#ifndef TURTLE_ACTIONLIB_MESSAGE_VELOCITY_H
#define TURTLE_ACTIONLIB_MESSAGE_VELOCITY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace turtle_actionlib
{
template <class ContainerAllocator>
struct Velocity_
{
  typedef Velocity_<ContainerAllocator> Type;

  Velocity_()
    : linear(0.0)
    , angular(0.0)  {
    }
  Velocity_(const ContainerAllocator& _alloc)
    : linear(0.0)
    , angular(0.0)  {
    }



   typedef float _linear_type;
  _linear_type linear;

   typedef float _angular_type;
  _angular_type angular;




  typedef boost::shared_ptr< ::turtle_actionlib::Velocity_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::turtle_actionlib::Velocity_<ContainerAllocator> const> ConstPtr;

}; // struct Velocity_

typedef ::turtle_actionlib::Velocity_<std::allocator<void> > Velocity;

typedef boost::shared_ptr< ::turtle_actionlib::Velocity > VelocityPtr;
typedef boost::shared_ptr< ::turtle_actionlib::Velocity const> VelocityConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::turtle_actionlib::Velocity_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::turtle_actionlib::Velocity_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace turtle_actionlib

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/install_isolated/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/install_isolated/share/actionlib_msgs/cmake/../msg'], 'turtle_actionlib': ['/opt/ros/src/common_tutorials/turtle_actionlib/msg', '/opt/ros/devel_isolated/turtle_actionlib/share/turtle_actionlib/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::turtle_actionlib::Velocity_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::turtle_actionlib::Velocity_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::turtle_actionlib::Velocity_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::turtle_actionlib::Velocity_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::turtle_actionlib::Velocity_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::turtle_actionlib::Velocity_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::turtle_actionlib::Velocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9d5c2dcd348ac8f76ce2a4307bd63a13";
  }

  static const char* value(const ::turtle_actionlib::Velocity_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9d5c2dcd348ac8f7ULL;
  static const uint64_t static_value2 = 0x6ce2a4307bd63a13ULL;
};

template<class ContainerAllocator>
struct DataType< ::turtle_actionlib::Velocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "turtle_actionlib/Velocity";
  }

  static const char* value(const ::turtle_actionlib::Velocity_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::turtle_actionlib::Velocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Copied from turtlesim https://github.com/ros/ros_tutorials/blob/f7da7779e82dcc3977b2c220a843cd86dd269832/turtlesim/msg/Velocity.msg. We had to copy this into this package since it has been replaced with geometry_msgs/Twist there and comforming to Twist requires to change code, which I doubt worth time it takes. So if you think it is, please go ahead make a patch.\n\
\n\
float32 linear\n\
float32 angular\n\
";
  }

  static const char* value(const ::turtle_actionlib::Velocity_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::turtle_actionlib::Velocity_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.linear);
      stream.next(m.angular);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct Velocity_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::turtle_actionlib::Velocity_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::turtle_actionlib::Velocity_<ContainerAllocator>& v)
  {
    s << indent << "linear: ";
    Printer<float>::stream(s, indent + "  ", v.linear);
    s << indent << "angular: ";
    Printer<float>::stream(s, indent + "  ", v.angular);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TURTLE_ACTIONLIB_MESSAGE_VELOCITY_H