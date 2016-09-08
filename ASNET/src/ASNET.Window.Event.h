#pragma once
#include<vector>
#include<functional>


#include"ASNET.Window.Keycode.h"
#include"ASNET.Graph.h"

//�򵥵��¼���
//�����е��麯������sender�������ݵ��Ǵ��ڵ�ָ��
//�����еı����صĺ��������ͨ��handler����ĺ�������sender�Ĳ��������Լ���ָ��
//��Ϊ���б����ؽ�ȥ�ĺ���Ҫ���Ǿ�̬�ģ������sender������ָ��������Լ�

namespace ASNET {
	class Window;
	namespace Event {

		//�¼�����
		enum class EventType :int {
			EventOther,
			EventMouseMove,
			EventMouseClick,
			EventMouseWheel,
			EventBoardClick
		};


		//Base Event
		struct EventBase {

		};


		//MouseMove Event
		struct EventMouseMove :EventBase {
			int x, y;
		};

		//enum of mouse button
		enum MouseButton {
			Left, Middle, Right
		};

		//MouseClick Event
		struct EventMouseClick :EventBase {
			int x, y;
			bool IsDown;
			MouseButton button;
		};

		//MouseWheel Event
		struct EventMouseWheel :EventBase {
			int x, y;
			int offest; //the mouse wheel move + is up,- is down
		};




		//BoardClick Event
		struct EventBoardClick :EventBase {
			Keycode keycode;
			bool IsDown;
		};

		//SizeChange Event
		struct EventSizeChange :EventBase {
			int last_width, last_height;
			int now_width, now_height;
		};


		
		typedef std::function<void(void*, EventBase*)>			EventBaseHandler; //�����¼�
		typedef std::function<void(void*, EventMouseMove*)>		EventMouseMoveHandler; //����ƶ��¼�
		typedef std::function<void(void*, EventMouseWheel*)>	EventMouseWheelHandler; //��껬�ֹ����¼�
		typedef std::function<void(void*, EventMouseClick*)>	EventMouseClickHandler; //������¼�
		typedef	std::function<void(void*, EventBoardClick*)>	EventBoardClickHandler; //���̰����¼�
		typedef std::function<void(void*, EventSizeChange*)>	EventSizeChangeHandler; //���ڴ�С�¼�

		typedef std::function<void(void*)>				        EventGetFocusHandler; //�õ������¼�
		typedef std::function<void(void*)>                      EventLostFocusHandler; //ʧȥ�����¼�



		typedef std::vector<ASNET::Event::EventBaseHandler>				EventBaseHandlers; //�����¼�����
		typedef std::vector<ASNET::Graph::EventGraphDrawHandler>		EventGraphDrawHandlers; //�����¼�����
		typedef std::vector<ASNET::Event::EventMouseMoveHandler>		EventMouseMoveHandlers; //����ƶ��¼�����
		typedef std::vector<ASNET::Event::EventMouseWheelHandler>		EventMouseWheelHandlers; //��껬�ֹ����¼����� 
		typedef std::vector<ASNET::Event::EventMouseClickHandler>		EventMouseClickHandlers; //������¼����� 
		typedef std::vector<ASNET::Event::EventBoardClickHandler>		EventBoardClickHandlers; //���̰����¼�����
		typedef std::vector<ASNET::Event::EventSizeChangeHandler>		EventSizeChangeHandlers; //���ڴ�С�¼�����

		typedef std::vector<ASNET::Event::EventGetFocusHandler>	        EventGetFocusHandlers; //��ȡ�����¼�����
		typedef std::vector<ASNET::Event::EventLostFocusHandler>	    EventLostFocusHandlers; //ʧȥ�����¼�����


		class EventHandler {
		public:
			friend ASNET::Event::EventBaseHandlers operator +=(
				ASNET::Event::EventBaseHandlers &handlers,
				ASNET::Event::EventBaseHandler handler
				);

			friend ASNET::Event::EventGraphDrawHandlers operator +=(
				ASNET::Event::EventGraphDrawHandlers &handlers,
				ASNET::Graph::EventGraphDrawHandler handler
				);

			friend ASNET::Event::EventMouseMoveHandlers operator +=(
				ASNET::Event::EventMouseMoveHandlers &handlers,
				ASNET::Event::EventMouseMoveHandler handler
				);

			friend ASNET::Event::EventMouseWheelHandlers operator +=(
				ASNET::Event::EventMouseWheelHandlers &handlers,
				ASNET::Event::EventMouseWheelHandler handler
				);

			friend ASNET::Event::EventMouseClickHandlers operator +=(
				ASNET::Event::EventMouseClickHandlers &handlers,
				ASNET::Event::EventMouseClickHandler handler
				);

			friend ASNET::Event::EventBoardClickHandlers operator +=(
				ASNET::Event::EventBoardClickHandlers &handlers,
				ASNET::Event::EventBoardClickHandler handler
				);

			friend ASNET::Event::EventSizeChangeHandlers operator +=(
				ASNET::Event::EventSizeChangeHandlers &handlers,
				ASNET::Event::EventSizeChangeHandler handler
				);

			friend ASNET::Event::EventGetFocusHandlers operator+=(
				ASNET::Event::EventGetFocusHandlers &handlers,
				ASNET::Event::EventGetFocusHandler handler
				);

		


			static auto GetSenderMessage(void* sender)->ASNET::Window*;

		};

		//��һ���¼�����������¼�����
		template<typename Handlers, typename EventArg>
		static void DoEventHandlers(Handlers handlers, void * sender, EventArg eventarg) {
			for (size_t i = 0; i < handlers.size(); i++)
				handlers[i](sender, eventarg);
		}

		template<typename Handlers>
		static void DoEventHandlers(Handlers handlers, void* sender) {
			for (size_t i = 0; i < handlers.size(); i++)
				handlers[i](sender);
		}

	}

}