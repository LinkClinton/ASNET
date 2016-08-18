#pragma once
#include<Window.h>
namespace ASNET {
	namespace Sample {

		

		//继承原本的窗口类
		class WindowSample :public ASNET::Window {
		private:
			int MousePosX; //鼠标位置
			int MousePosY; //鼠标位置

		
			friend class PageSample; //让这个类可以访问其私有成员
		protected:
			void OnLoading()override;
			//虚函数自己重新写，这个是关于鼠标移动的,这个就是在鼠标移动的时候会被运行
			//sender 通常情况下是发送消息的窗口的指针，另外一个参数就是其数据消息
			void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e)override;
			//或者自己写一个函数加载进去,参数要和函数要求一样,要前面加static
			static void MyMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
		public:
			WindowSample(); //重新写构造函数
		};

		//继承原本的页面，页面其实就是一个窗口的内容
		//一个窗口的页面可以切换
		class PageSample :public ASNET::Page::Page {
		protected:
			//当这个页面被设置为要用的页面的时候运行
			void OnLoading(void* sender, void* any)override;
			//绘制这个页面
			void OnDraw(void* sender, ASNET::Graph::Graph* render)override;
		public:
			PageSample(); //构造函数重新写
		};

	}
}