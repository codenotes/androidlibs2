// Generated by gencpp from file triangulator/triangulatorCommand.msg
// DO NOT EDIT!


#ifndef TRIANGULATOR_MESSAGE_TRIANGULATORCOMMAND_H
#define TRIANGULATOR_MESSAGE_TRIANGULATORCOMMAND_H

#include <ros/service_traits.h>


#include <triangulator/triangulatorCommandRequest.h>
#include <triangulator/triangulatorCommandResponse.h>


namespace triangulator
{

struct triangulatorCommand
{

typedef triangulatorCommandRequest Request;
typedef triangulatorCommandResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct triangulatorCommand
} // namespace triangulator


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::triangulator::triangulatorCommand > {
  static const char* value()
  {
    return "b2d0b1f05b3a2d93cc4772e898169482";
  }

  static const char* value(const ::triangulator::triangulatorCommand&) { return value(); }
};

template<>
struct DataType< ::triangulator::triangulatorCommand > {
  static const char* value()
  {
    return "triangulator/triangulatorCommand";
  }

  static const char* value(const ::triangulator::triangulatorCommand&) { return value(); }
};


// service_traits::MD5Sum< ::triangulator::triangulatorCommandRequest> should match 
// service_traits::MD5Sum< ::triangulator::triangulatorCommand > 
template<>
struct MD5Sum< ::triangulator::triangulatorCommandRequest>
{
  static const char* value()
  {
    return MD5Sum< ::triangulator::triangulatorCommand >::value();
  }
  static const char* value(const ::triangulator::triangulatorCommandRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::triangulator::triangulatorCommandRequest> should match 
// service_traits::DataType< ::triangulator::triangulatorCommand > 
template<>
struct DataType< ::triangulator::triangulatorCommandRequest>
{
  static const char* value()
  {
    return DataType< ::triangulator::triangulatorCommand >::value();
  }
  static const char* value(const ::triangulator::triangulatorCommandRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::triangulator::triangulatorCommandResponse> should match 
// service_traits::MD5Sum< ::triangulator::triangulatorCommand > 
template<>
struct MD5Sum< ::triangulator::triangulatorCommandResponse>
{
  static const char* value()
  {
    return MD5Sum< ::triangulator::triangulatorCommand >::value();
  }
  static const char* value(const ::triangulator::triangulatorCommandResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::triangulator::triangulatorCommandResponse> should match 
// service_traits::DataType< ::triangulator::triangulatorCommand > 
template<>
struct DataType< ::triangulator::triangulatorCommandResponse>
{
  static const char* value()
  {
    return DataType< ::triangulator::triangulatorCommand >::value();
  }
  static const char* value(const ::triangulator::triangulatorCommandResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // TRIANGULATOR_MESSAGE_TRIANGULATORCOMMAND_H
