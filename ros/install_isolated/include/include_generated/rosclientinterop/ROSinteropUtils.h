#define MAX_ROS_MESSAGE_SIZE 1813722

#ifdef WIN32
 extern thread_local uint8_t * msgbuf ;
#else
 extern __thread uint8_t * msgbuf ;
#endif



namespace rosinterop
{

	class interUtil
	{
	public:

		static bool initSimple(const char * nodeName)
		{
			return ROSInitSimple(nodeName);

		}

		static void killPub(const char * topic)
		{
			notifyPublisherQueue(topic, 0);
		}

		static void killSub(const char * topic)
		{
			notifySubscriberQueue(topic, 0);
		}



		template <class T>
		static void spinSub(char * topic, int loopRate, int qsize, bool latching)
		{
			std::string s1, s2, s3;

			s1 = ros::message_traits::MD5Sum< T>::value();
			s2 = ros::message_traits::DataType<T>::value();
			s3 = ros::message_traits::Definition<T>::value();
			spinSubscriber(topic, s1.c_str(), s2.c_str(), s3.c_str(), loopRate, qsize, latching);


		}


		template <class T>
		static void spinPub(char * topic, int loopRate, int qsize, bool latching)
		{

			std::string s1, s2, s3;

			s1 = ros::message_traits::MD5Sum< T>::value();
			s2 = ros::message_traits::DataType<T>::value();
			s3 = ros::message_traits::Definition<T>::value();
			spinPublisher(topic, s1.c_str(), s2.c_str(), s3.c_str(), loopRate, qsize, latching);


		}

		template <class T>
		static bool getMsg(const char * topic, T& msg)
		{

			//uint8_t temp[SIZE];
		
			if(!msgbuf)
				msgbuf= new uint8_t[MAX_ROS_MESSAGE_SIZE];

			//uint8_t * temp = new uint8_t[MAX_ROS_MESSAGE_SIZE];

			long size;

			//if (getMessage(topic, temp, &size))
			if (getMessage(topic, msgbuf, &size))
			{
				//ros::serialization::deserializeMessage<T>(temp, msg);
				ros::serialization::IStream stream(msgbuf, size);
				ros::serialization::deserialize(stream, msg);
			
				return true;
			}
			else
			{
			
				return false; 
				
			}
		}

		template <class T>
		static void pubMsg(char * topic, T msg)
		{
			ros::SerializedMessage m = ros::serialization::serializeMessage<T>(msg);
			pubMessage(topic, m.buf.get(), m.num_bytes);


		}



		template <class T>
		static bool getMsgBag(const char * bagFile, const char * topic, T& msg)
		{

		
		}




	};
}