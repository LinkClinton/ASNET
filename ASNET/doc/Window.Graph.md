```cpp
class Font { //字体类型，这个类似使用的时候请声明指针
		private:
			ASNET::Graph::Graph* ParentGraph;

			IDWriteTextFormat*	 textformat;
			friend class Graph;
		public:
			Font(ASNET::Graph::Graph* Graph); //这个构造函数基本上不是给使用者使用
			~Font();
			//如果你不要用了，最好delete他
			auto FontSize()->float;
            //或者创建的字体的大小
			void reset(ASNET::Graph::Word fontname, float fontsize);
			//在创建字体后想重写创建可以直接reset
			//参数在后面解释
		};

enum class TextAlign {
			Left, Center, Right, Top, Bottom
		};
		//绘制文字的时候文字的布局。左右格局只能左右
		//上下只能上下，中心是通用的

```
概述：
>其实就是一个字体的结构，使用的话就是声明他，必须用指针，然后用Graph类加载他。不用他了的话最好delete他。

```cpp
	class Image {//图片的结构，同样声明必须声明指针
		private:
			ASNET::Graph::Graph* ParentGraph;

			ID2D1Bitmap* bitmap;
			friend class Graph;
		public:
			Image(ASNET::Graph::Graph* Graph);  //构造函数基本上不是给使用者使用
			~Image(); //析构函数
			auto GetWidth()->float;
			auto GetHieght()->float;
            //获得图片的大小
            
			void reset(ASNET::Graph::Word filename);
			//创建之后重新创建
		};
```

概述：
>基本上就是一个图片类型，使用的话就是声明他，必须用指针，然后用Graph类加载他。不用他了的话最好delete他。

```cpp
class Graph { //这个类是不要去继承的
		protected:
			//Information
			HWND					g_hwnd;  //窗口句柄
			int						g_width; //窗口宽度
			int						g_height; //窗口高度
			bool					g_windowed; //是否窗口化
		protected:
			//Direct2D
			ID2D1Factory*			g_factory; 

			ID2D1RenderTarget*      g_devicecontext2d;

			//d2d1_1
			//ID2D1Device*            g_device2d;
			//ID2D1DeviceContext*     g_devicecontext2d;

			//Direct3D11
			ID3D11Device*			g_device3d;
			IDXGISwapChain*			g_swapchain;
			ID3D11DeviceContext*    g_devicecontext3d;
			ID3D11RenderTargetView* g_rendertargetview;
			ID3D11DepthStencilView* g_depthstencilview;

			//Dwrite
			IDWriteFactory*			g_writefactory;

			//IWIC
			IWICImagingFactory*     g_imagefactory;
			//以上使用者没必要理解
			friend class Window;
			friend class Image;
			friend class Font;
			void Initalize(HWND hwnd, bool IsWindowed);
		public:
			Graph(); //构造函数，不是使用者使用
			Graph(HWND hwnd, bool IsWindowed = true);
			//构造函数，是使用者使用，最好声明指针类型，然后在Window类里面声明他
			~Graph();
			virtual void Clear(ASNET::Graph::Color color = ASNET::Graph::Color::White);//清理，在绘制前必须调用

			virtual void Present();
            //刷新
			virtual void DrawLine(ASNET::Graph::Point P1,
				ASNET::Graph::Point P2, ASNET::Graph::Color color, float width = 1.0f);
            //绘制线
			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = ASNET::Graph::Color::White);
            //绘制矩形，witdh是线的宽度，IsFill是是否填充矩形
			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);
            //绘制图片，rect是绘制的矩形范围，图片会因此放缩
			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = ASNET::Graph::Color::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);
			//绘制文本内容，将其绘制在一个rect里面，然后后面两个参数决定其在rect里面的是居中还是什么
			virtual void LoadImage(ASNET::Graph::Word filename,
				ASNET::Graph::Image* &image);
            //加载图片，第一个参数是图片文件名
			virtual void LoadFont(ASNET::Graph::Font* &font,
				ASNET::Graph::Word fontname, float fontsize);
            //加载字体，fontname是在Windows自己里面的字体名字
            //fontsize是字体大小


		};
```

概述:
>一个简单的绘制接口，可以绘制一些质量还可以的简单图形。
>字体方面对高DPI的支持不够好